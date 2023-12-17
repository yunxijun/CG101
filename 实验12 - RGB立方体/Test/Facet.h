#pragma once
#include "Vector3.h"
class CFacet
{
public:
	CFacet(void);
	virtual ~CFacet(void);
public:
	int Number;//表面顶点数目
	int Index[4];//面的顶点索引号
};

