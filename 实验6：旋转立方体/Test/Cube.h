#pragma once
#include"P3.h"
#include "Facet.h"

class CCube
{
public:
	CCube(void);
	virtual ~CCube(void);
	void ReadPoint(void);//读入点表
	void ReadFacet(void);//读入面表
	CP3*  GetVertexArrayName(void);//得到顶点数组名
	void Draw(CDC* pDC);//绘制立方体线框
private:
	CP3 P[8];//点表
	CFacet F[6];//面表
};