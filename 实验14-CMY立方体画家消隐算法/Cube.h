#pragma once
#include"Facet.h"

class CCube
{
public:
	CCube(void);
	virtual ~CCube(void);
	void ReadPoint(void);//������
	void ReadFacet(void);//�������
public://���г�Ա������ά�����л���
	CP3 P[8];//�������
	CFacet F[6];//�������
};

