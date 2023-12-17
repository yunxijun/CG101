#pragma once
#include"Point2.h"

class CLine
{
public:
	CLine(void);
	virtual ~CLine(void);
	void MoveTo(CDC* pDC, CPoint2 p0);//移动到指定位置
	void MoveTo(CDC* pDC, int x0, int y0, CRGB c0);//重载函数
	void LineTo(CDC* pDC, CPoint2 p1);//绘制直线，不含终点
	void LineTo(CDC* pDC, int x1, int y1, CRGB c1);//重载函数
	CRGB LinearInterp(double t, double tStart, double tEnd, CRGB cStart, CRGB cEnd);//颜色线性插值
private:
	CPoint2 P0;//起点
	CPoint2 P1;//终点
};

