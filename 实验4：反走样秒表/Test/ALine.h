#pragma once
#include"P2.h"
class CALine
{
public:
	CALine(void);
	virtual ~CALine(void);
	void MoveTo(CDC* pDC, CP2 p0);//�ƶ���ָ��λ��
	void MoveTo(CDC* pDC, double x0, double y0);
	void LineTo(CDC* pDC, CP2 p1);//����ֱ�ߣ������յ�
	void LineTo(CDC* pDC, double x1, double y1);
private:
	CP2 P0;//���
	CP2 P1;//�յ�
};