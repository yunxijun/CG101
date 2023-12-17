#include "pch.h"
#include "Bar.h"

CBar::CBar(void)
{
}

CBar::~CBar(void)
{
}

void CBar::SetParameter(int nLength, int nHeight, int nWidth, CRGB clrLeft, CRGB clrRight)//设置参数
{
	a = nLength;//长度
	b = nHeight;//高度
	c = nWidth;//宽度
	this->clrLeft = clrLeft;//左半部分颜色
	this->clrRight = clrRight;//右半部分颜色
}

void CBar::ReadPoint(void)//点表
{
	P[0].x = -a/2, P[0].y = -b/2, P[0].z = -c/2, P[0].c = clrLeft;
	P[1].x = +a/2, P[1].y = -b/2, P[1].z = -c/2, P[1].c = clrRight;
	P[2].x = +a/2, P[2].y = +b/2, P[2].z = -c/2, P[2].c = clrRight;
	P[3].x = -a/2, P[3].y = +b/2, P[3].z = -c/2, P[3].c = clrLeft;
	P[4].x = -a/2, P[4].y = -b/2, P[4].z = +c/2, P[4].c = clrLeft;
	P[5].x = +a/2, P[5].y = -b/2, P[5].z = +c/2, P[5].c = clrRight;
	P[6].x = +a/2, P[6].y = +b/2, P[6].z = +c/2, P[6].c = clrRight;
	P[7].x = -a/2, P[7].y = +b/2, P[7].z = +c/2, P[7].c = clrLeft;
}

void CBar::ReadFacet(void)//面表
{
	F[0].Number = 4;F[0].Index[0] = 4;F[0].Index[1] = 5;F[0].Index[2] = 6;F[0].Index[3] = 7;//前面
	F[1].Number = 4;F[1].Index[0] = 0;F[1].Index[1] = 3;F[1].Index[2] = 2;F[1].Index[3] = 1;//后面
	F[2].Number = 4;F[2].Index[0] = 0;F[2].Index[1] = 4;F[2].Index[2] = 7;F[2].Index[3] = 3;//左面
	F[3].Number = 4;F[3].Index[0] = 1;F[3].Index[1] = 2;F[3].Index[2] = 6;F[3].Index[3] = 5;//右面
	F[4].Number = 4;F[4].Index[0] = 2;F[4].Index[1] = 3;F[4].Index[2] = 7;F[4].Index[3] = 6;//顶面
	F[5].Number = 4;F[5].Index[0] = 0;F[5].Index[1] = 1;F[5].Index[2] = 5;F[5].Index[3] = 4;//底面
}

void CBar::Draw(CDC* pDC, CZBuffer* pZBuffer)
{
	CP3 ScreenPoint[4];//屏幕坐标三维点
	for(int nFacet = 0; nFacet < 6; nFacet++)
	{
		for(int nPoint = 0; nPoint < F[nFacet].Number; nPoint++)//顶点循环
			ScreenPoint[nPoint] = projection.PerspectiveProjection3(P[F[nFacet].Index[nPoint]]);//投影
		pZBuffer->SetPoint(ScreenPoint[0], ScreenPoint[2], ScreenPoint[3]);//上三角形
		pZBuffer->GouraudShader(pDC);
		pZBuffer->SetPoint(ScreenPoint[0], ScreenPoint[1], ScreenPoint[2]);//下三角形
		pZBuffer->GouraudShader(pDC);
	}
}