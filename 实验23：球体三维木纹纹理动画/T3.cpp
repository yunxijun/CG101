#include "pch.h"
#include "T3.h"


CT3::CT3(void)
{
	w = 0.0;
}

CT3::CT3(double u, double v, double w) :CT2(u, v)
{
	this->w = w;
}

CT3::~CT3(void)
{
}

CT3 operator + (const CT3 &t0, const CT3 &t1)//和
{
	CT3 result;
	result.u = t0.u + t1.u;
	result.v = t0.v + t1.v;
	result.w = t0.w + t1.w;
	return result;
}

CT3 operator - (const CT3 &t0, const CT3 &t1)//差
{
	CT3 result;
	result.u = t0.u - t1.u;
	result.v = t0.v - t1.v;
	result.w = t0.w - t1.w;
	return result;
}

CT3 operator * (const CT3 &t, double scalar)//点和常量的积
{
	return CT3(t.u * scalar, t.v * scalar, t.w * scalar);
}

CT3 operator * (double scalar, const CT3 &t)//常量和点的积
{
	return CT3(t.u * scalar, t.v * scalar, t.w * scalar);
}

CT3 operator / (const CT3 &t, double scalar)//数除
{
	if (fabs(scalar) < 1e-4)
		scalar = 1.0;
	CT3 result;
	result.u = t.u / scalar;
	result.v = t.v / scalar;
	result.w = t.w / scalar;
	return result;
}

