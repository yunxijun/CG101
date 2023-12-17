#pragma once
#include "Facet.h"
#include "Projection.h"
#include "ZBuffer.h"

class CBar
{
public:
	CBar(void);
	virtual ~CBar(void);
	void SetParameter(int nLength, int nHeight, int nWidth, CRGB clrLeft, CRGB clrRight);//���ò���
	void ReadPoint(void);//������
	void ReadFacet(void);//�������
	void Draw(CDC* pDC, CZBuffer* pZBuffer);//����ͼ��
public:
	CP3 P[8];//��������
private:
	int a, b, c;//���ȡ��߶ȡ����
	CRGB clrLeft;//��벿����ɫ
	CRGB clrRight;//�Ұ벿����ɫ
	CFacet F[6];//��������
	CProjection projection;//ͶӰ
};