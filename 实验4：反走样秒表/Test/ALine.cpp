#include "pch.h"
#include "ALine.h"
#define ROUND(d) int(d + 0.5)
#define COLOR(c) int(RGB(c.red * 255, c.green * 255, c.blue * 255))

CALine::CALine(void)
{
}


CALine::~CALine(void)
{
}
void CALine::MoveTo(CDC* pDC, CP2 p0)//绘制直线起点函数
{
	P0 = p0;
}
void CALine::MoveTo(CDC* pDC, double x0, double y0)//重载函数
{
	MoveTo(pDC, CP2(x0, y0));
}

void CALine::LineTo(CDC* pDC, CP2 p1)//绘制直线终点函数
{
	P1 = p1;
	double dx = abs(P1.x - P0.x);
	double dy = abs(P1.y - P0.y);
	BOOL bInterChange = FALSE;
	double e, signX, signY, temp;
	signX = (P1.x > P0.x) ? 1 : ((P1.x < P0.x) ? -1 : 0);
	signY = (P1.y > P0.y) ? 1 : ((P1.y < P0.y) ? -1 : 0);
	if (dy > dx)
	{
		temp = dx;
		dx = dy;
		dy = temp;
		bInterChange = TRUE;
	}
	e =0;
	CP2 p = P0;//从起点开始绘制直线
	for (int i = 1; i <= dx; i++)
	{
		CRGB c0(e, e, e);
		CRGB c1(1 - e, 1 - e, 1 - e);
		if(bInterChange)//y为主位移方向
		{
			pDC->SetPixelV(ROUND(p.x + signX), ROUND(p.y), COLOR(c1));
			pDC->SetPixelV(ROUND(p.x), ROUND(p.y), COLOR(c0));
		}
		else//x为主位移方向
		{
			pDC->SetPixelV(ROUND(p.x), ROUND(p.y + signY), COLOR(c1));
			pDC->SetPixelV(ROUND(p.x), ROUND(p.y), COLOR(c0));
		}
		if (bInterChange)
			p.y += signY;
		else
			p.x += signX;
		e += (dy/dx);
		if (e >= 1.0)
		{
			if (bInterChange)
				p.x += signX;
			else
				p.y += signY;
			e --;
		}
	}
	P0 = p1;
}

void CALine::LineTo(CDC* pDC, double x1, double y1)//重载函数
{
	LineTo(pDC, CP2(x1, y1));
}