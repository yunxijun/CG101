#pragma once
#include"P2.h"

class CBezierCurve//����Bezier����
{
public:
	CBezierCurve(void);
	virtual ~CBezierCurve(void);
	void ReadPoint(CP2* P);//������Ƶ�
	void DrawCurve(CDC* pDC);//��������
	void DrawPolygon(CDC* pDC);//���ƿ��ƶ����
private:
	CP2 P[4];//���Ƶ�����
};