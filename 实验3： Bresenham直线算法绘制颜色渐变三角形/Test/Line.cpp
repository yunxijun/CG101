#include "pch.h"
#include "Line.h"
#define COLOR(c) int(RGB(c.red * 255, c.green * 255, c.blue * 255))

CLine::CLine(void)
{
}

CLine::~CLine(void)
{	
}

void CLine::MoveTo(CDC* pDC, CPoint2 p0)
{
	P0 = p0;
}

void CLine::MoveTo(CDC* pDC, int x0, int y0, CRGB c0)//重载函数
{
	P0 = CPoint2(x0, y0, c0);
}

void CLine::LineTo(CDC* pDC, CPoint2 p1)//绘制直线函数
{
	P1 = p1; 
	int dx = abs(P1.x - P0.x);
	int dy = abs(P1.y - P0.y);
	BOOL bInterChange = FALSE;
	int e, signX, signY, temp;
	signX = (P1.x > P0.x) ? 1 : ((P1.x < P0.x) ? -1 : 0);
	signY = (P1.y > P0.y) ? 1 : ((P1.y < P0.y) ? -1 : 0);
	if (dy > dx)
	{
		temp = dx;
		dx = dy;
		dy = temp;
		bInterChange = TRUE;
	}
	e = -dx;
	CPoint2 p = P0;//从起点开始绘制直线
	for (int i = 1; i <= dx; i++)
	{
		p.c = LinearInterp(p.x, P0.x, P1.x, P0.c, P1.c);
		if (P0.x == P1.x)
			p.c = LinearInterp(p.y, P0.y, P1.y, P0.c, P1.c);
		pDC->SetPixelV(p.x, p.y, COLOR(p.c));
		if (bInterChange)
			p.y += signY;
		else
			p.x += signX;
		e += 2 * dy;
		if (e >= 0)
		{
			if (bInterChange)
				p.x += signX;
			else
				p.y += signY;
			e -= 2 * dx;
		}
	}
	P0 = p1;
}

void CLine::LineTo(CDC* pDC, int x1, int y1, CRGB c1)//重载绘制直线函数
{
	LineTo(pDC, CPoint2(x1, y1, c1));
}

CRGB CLine::LinearInterp(double t, double tStart, double tEnd, CRGB cStart, CRGB cEnd)//颜色线性插值
{
	CRGB color;
	color = (t - tEnd) / (tStart - tEnd) * cStart + (t - tStart) / (tEnd - tStart) * cEnd;
	return color;
}
