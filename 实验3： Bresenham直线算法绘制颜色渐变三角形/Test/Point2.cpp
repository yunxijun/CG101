#include "pch.h"
#include "Point2.h"

CPoint2::CPoint2(void)
{
	x = 0;
	y = 0;
	c = CRGB(0.0, 0.0, 0.0);
}

CPoint2::CPoint2(int x, int y)
{
	this->x = x;
	this->y = y;
	this->c = CRGB(0.0, 0.0, 0.0);
}

CPoint2::CPoint2(int x, int y, CRGB c)
{
	this->x = x;
	this->y = y;
	this->c = c;
}

CPoint2::~CPoint2(void)
{
}
