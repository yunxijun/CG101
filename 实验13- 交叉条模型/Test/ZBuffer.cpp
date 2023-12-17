#include "pch.h"
#include "ZBuffer.h"
#define ROUND(d) int(d)
#define COLOR(c) int(RGB(c.red * 255, c.green * 255, c.blue * 255))

CZBuffer::CZBuffer(void)
{
}

CZBuffer::~CZBuffer(void)
{
	for(int i = 0;i < nWidth;i++)
	{
		delete[] zBuffer[i];
		zBuffer[i] = NULL;
	}
	if(zBuffer != NULL)
	{
		delete zBuffer;
		zBuffer = NULL;
	}
}

void CZBuffer::SetPoint(CP3 P0, CP3 P1, CP3 P2)
{
	this->P0 = P0;
	this->P1 = P1;
	this->P2 = P2;
	point0.x = ROUND(P0.x);
	point0.y = ROUND(P0.y);
	point0.z = P0.z;
	point0.c = P0.c;
	point1.x = ROUND(P1.x);
	point1.y = ROUND(P1.y);
	point1.z = P1.z;
	point1.c = P1.c;
	point2.x = ROUND(P2.x);
	point2.y = ROUND(P2.y);
	point2.z = P2.z;
	point2.c = P2.c;
}

void CZBuffer::GouraudShader(CDC* pDC)
{
	SortVertex();//三角形顶点排序
	//定义三角形覆盖的扫描线条数
	int nTotalLine = point1.y - point0.y + 1;
	//定义span的起点与终点数组
	SpanLeft = new CPoint2[nTotalLine];
	SpanRight = new CPoint2[nTotalLine];
	//判断三角形与P0P1边的位置关系，0-1-2为右手系
	int nDeltz = (point1.x - point0.x) * (point2.y - point0.y) - (point1.y - point0.y) * (point2.x - point0.x);//面法向量的z分量
	if (nDeltz > 0)//三角形位于P0P1边的左侧
	{
		nIndex = 0;
		EdgeFlag(point0, point2, TRUE);
		EdgeFlag(point2, point1, TRUE);
		nIndex = 0;
		EdgeFlag(point0, point1, FALSE);
	}
	else//三角形位于P0P1边的右侧
	{
		nIndex = 0;
		EdgeFlag(point0, point1, TRUE);
		nIndex = 0;
		EdgeFlag(point0, point2, FALSE);
		EdgeFlag(point2, point1, FALSE);
	}
	double	CurrentDepth = 0.0;//当前扫描线的深度
	CVector3 Vector01(P0, P1), Vector02(P0, P2);
	CVector3 fNormal = CrossProduct(Vector01, Vector02);
	double A = fNormal.x, B = fNormal.y, C = fNormal.z;//平面方程Ax+By+Cz＋D=0的系数
	double D = -A * P0.x - B * P0.y - C * P0.z;//系数D
	if(fabs(C) < 1e-4)
		C = 1.0;
	double DepthStep = -A/C;//扫描线深度步长
	for(int y = point0.y ; y < point1.y; y++)//下闭上开
	{
		int n = y - point0.y;
		for(int x = SpanLeft[n].x; x < SpanRight[n].x; x++)//左闭右开
		{
			CurrentDepth = -(A * x + B * y + D) / C;//z=-(Ax+By+D)/C
			CRGB clr = LinearInterp(x, SpanLeft[n].x, SpanRight[n].x, SpanLeft[n].c, SpanRight[n].c);
			if(CurrentDepth <= zBuffer[x + nWidth/2][y + nHeight/2])//如果当前采样点的深度小于帧缓冲器中原采样点的深度
			{
				zBuffer[x + nWidth/2][y + nHeight/2] = CurrentDepth;//使用当前采样点的深度更新深度缓冲器
				pDC->SetPixelV(x, y, COLOR(clr));
			}
			CurrentDepth += DepthStep;
		}
	}
	if(SpanLeft)
	{
		delete[]SpanLeft;
		SpanLeft = NULL;
	}
	if(SpanRight)
	{
		delete[]SpanRight;
		SpanRight = NULL;
	}
}

void CZBuffer::EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature)
{
	int dx = PEnd.x - PStart.x;
	int dy = PEnd.y - PStart.y;
	double m = double(dx) / dy;
	double x = PStart.x;
	for (int y = PStart.y; y < PEnd.y; y++)
	{
		CRGB crColor = LinearInterp(y, PStart.y, PEnd.y, PStart.c, PEnd.c);
		if (bFeature)
			SpanLeft[nIndex++] = CPoint2(ROUND(x), y, crColor);
		else
			SpanRight[nIndex++] = CPoint2(ROUND(x), y, crColor);
		x += m;
	}
}

void CZBuffer::SortVertex(void)
{
	CPoint3 pt[3];
	pt[0] = point0;
	pt[1] = point1;
	pt[2] = point2;
	for (int i = 0; i < 2; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			int k = i;
			if (pt[k].y >= pt[j].y)
				k = j;
			if (k == j)
			{
				CPoint3 ptTemp = pt[i];
				pt[i] = pt[k];
				pt[k] = ptTemp;
			}
		}
	}
	point0 = pt[0];
	point1 = pt[2];
	point2 = pt[1];
}

CRGB CZBuffer::LinearInterp(double t, double tStart, double tEnd, CRGB cStart, CRGB cEnd)//颜色线性插值
{
	CRGB color;
	color = (tEnd - t) / (tEnd - tStart) * cStart + (t - tStart) / (tEnd - tStart) * cEnd;
	return color;
}

void CZBuffer::InitialDepthBuffer(int nWidth, int nHeight,double zDepth)//初始化深度缓冲
{
	this->nWidth  = nWidth, this->nHeight = nHeight;
	zBuffer = new double *[nWidth];
	for(int i = 0;i < nWidth;i++)
		zBuffer[i] = new double[nHeight];
	for(int i = 0;i < nWidth;i++)//初始化深度
		for(int j=0;j < nHeight;j++)
			zBuffer[i][j] = zDepth;
}