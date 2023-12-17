#pragma once
#include"Point2.h"

class CLine
{
public:
	CLine(void);
	virtual ~CLine(void);
	void MoveTo(CDC* pDC, CPoint2 p0);//�ƶ���ָ��λ��
	void MoveTo(CDC* pDC, int x0, int y0, CRGB c0);//���غ���
	void LineTo(CDC* pDC, CPoint2 p1);//����ֱ�ߣ������յ�
	void LineTo(CDC* pDC, int x1, int y1, CRGB c1);//���غ���
	CRGB LinearInterp(double t, double tStart, double tEnd, CRGB cStart, CRGB cEnd);//��ɫ���Բ�ֵ
private:
	CPoint2 P0;//���
	CPoint2 P1;//�յ�
};

