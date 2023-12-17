#pragma once
#include "Facet.h"
#include "Projection.h"
#include "Triangle.h"

class CCube
{
public:
	CCube(void);
	virtual ~CCube(void);
	CP3* GetVertexArrayName(void);//���������
	void ReadPoint(void);//������
	void ReadFacet(void);//�������	
	void Draw(CDC* pDC);//����ͼ��
private:
	CP3 P[8];//�������
	CFacet F[6];//�������
	CProjection projection;//ͶӰ
};

