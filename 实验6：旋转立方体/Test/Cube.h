#pragma once
#include"P3.h"
#include "Facet.h"

class CCube
{
public:
	CCube(void);
	virtual ~CCube(void);
	void ReadPoint(void);//������
	void ReadFacet(void);//�������
	CP3*  GetVertexArrayName(void);//�õ�����������
	void Draw(CDC* pDC);//�����������߿�
private:
	CP3 P[8];//���
	CFacet F[6];//���
};