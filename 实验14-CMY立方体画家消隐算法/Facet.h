#pragma once
#include"Vector3.h"

class CFacet
{
public:
	CFacet(void);
	virtual ~CFacet(void);
public:
	int Number;//顶点数
	int Index[4];//顶点索引号	
	double fMaxDepth; //深度
};

