#pragma once
#include"P2.h"

class CBezierCurve//三次Bezier曲线
{
public:
	CBezierCurve(void);
	virtual ~CBezierCurve(void);
	void ReadPoint(CP2* P);//读入控制点
	void DrawCurve(CDC* pDC);//绘制曲线
	void DrawPolygon(CDC* pDC);//绘制控制多边形
private:
	CP2 P[4];//控制点数组
};