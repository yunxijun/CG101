#pragma once
#include "Point3.h"
#include "P3.h"
#include "Vector3.h"

class CZBuffer
{
public:
	CZBuffer(void);
	virtual ~CZBuffer(void);
	void SetPoint(CP3 P0, CP3 P1, CP3 P2);//设置三角形顶点
	void InitialDepthBuffer(int nWidth, int nHeight, double zDepth);//初始化深度缓冲器
	void GouraudShader(CDC* pDC);//光滑着色
private:
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//打边标记
	CRGB LinearInterp(double t, double tStart, double tEnd, CRGB cStart, CRGB cEnd);//颜色线性插值
	void SortVertex(void);//顶点排序
private:
	CP3 P0, P1, P2;//三角形的浮点数顶点
	CPoint3 point0, point1, point2;//三角形的整数顶点坐标
	CPoint2* SpanLeft; //跨度的起点数组标志
	CPoint2* SpanRight;//跨度的终点数组标志
	int nIndex;//记录扫描线条数
	double** zBuffer;//深度缓冲区
	int nWidth, nHeight;//缓冲区宽度和高度
};

