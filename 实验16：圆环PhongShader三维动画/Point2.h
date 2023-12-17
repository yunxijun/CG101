#pragma once
#include "RGB.h"
#include "Vector3.h"

class CPoint2
{
public:
	CPoint2(void);
	CPoint2(int x, int y);
	CPoint2(int x, int y, CRGB c);
	CPoint2(int x, int y, CVector3 n);
	virtual ~CPoint2(void);	
public:
	int x, y;//����
	CRGB c;//��ɫ
	CVector3 n;//������
};

