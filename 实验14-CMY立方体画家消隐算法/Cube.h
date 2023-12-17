#pragma once
#include"Facet.h"

class CCube
{
public:
	CCube(void);
	virtual ~CCube(void);
	void ReadPoint(void);//读入点表
	void ReadFacet(void);//读入面表
public://公有成员方便三维场景中汇总
	CP3 P[8];//点表数组
	CFacet F[6];//面表数组
};

