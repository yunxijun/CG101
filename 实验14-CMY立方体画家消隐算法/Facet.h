#pragma once
#include"Vector3.h"

class CFacet
{
public:
	CFacet(void);
	virtual ~CFacet(void);
public:
	int Number;//������
	int Index[4];//����������	
	double fMaxDepth; //���
};

