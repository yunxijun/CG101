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
	int x, y;//坐标
	CRGB c;//颜色
	CVector3 n;//法向量
};

