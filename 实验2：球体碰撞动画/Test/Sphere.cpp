#include "pch.h"
#include "Sphere.h"


CSphere::CSphere(void)
{
}


CSphere::~CSphere(void)
{
}

void CSphere::Draw(CDC* pDC)
{
	CPoint TopLet(CenterPoint.x - R, CenterPoint.y - R);
	CPoint BottomRight(CenterPoint.x + R, CenterPoint.y + R);
	CRect Square(TopLet, BottomRight);
	pDC->Ellipse(Square);
}