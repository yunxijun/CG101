#pragma once
#include"BezierCurve.h"

class CCircle
{
public:
	CCircle(void);
	virtual ~CCircle(void);
	void ReadPoint(void);//������Ƶ��
	CP2*  GetVertexArrayName(void);//�õ�����������
	void Draw(CDC* pDC);//��������
private:
	CP2 P[12];//���Ƶ�����
	CBezierCurve bezier[4];//���߶�
};