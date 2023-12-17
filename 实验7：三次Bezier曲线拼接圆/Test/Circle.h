#pragma once
#include"BezierCurve.h"

class CCircle
{
public:
	CCircle(void);
	virtual ~CCircle(void);
	void ReadPoint(void);//读入控制点表
	CP2*  GetVertexArrayName(void);//得到顶点数组名
	void Draw(CDC* pDC);//绘制曲线
private:
	CP2 P[12];//控制点数组
	CBezierCurve bezier[4];//曲线段
};