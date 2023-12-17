#pragma once
#include "Facet.h"
#include "Projection.h"
#include "ZBuffer.h"

class CBar
{
public:
	CBar(void);
	virtual ~CBar(void);
	void SetParameter(int nLength, int nHeight, int nWidth, CRGB clrLeft, CRGB clrRight);//设置参数
	void ReadPoint(void);//读入点表
	void ReadFacet(void);//读入面表
	void Draw(CDC* pDC, CZBuffer* pZBuffer);//绘制图形
public:
	CP3 P[8];//顶点数组
private:
	int a, b, c;//长度、高度、宽度
	CRGB clrLeft;//左半部分颜色
	CRGB clrRight;//右半部分颜色
	CFacet F[6];//表面数组
	CProjection projection;//投影
};