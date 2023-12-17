#pragma once
#include "Facet.h"
#include "Projection.h"
#include "Triangle.h"

class CCube
{
public:
	CCube(void);
	virtual ~CCube(void);
	CP3* GetVertexArrayName(void);//获得数组名
	void ReadPoint(void);//读入点表
	void ReadFacet(void);//读入面表	
	void Draw(CDC* pDC);//绘制图形
private:
	CP3 P[8];//点表数组
	CFacet F[6];//面表数组
	CProjection projection;//投影
};

