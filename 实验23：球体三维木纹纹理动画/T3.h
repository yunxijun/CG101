#pragma once
#include "T2.h"

class CT3 :public CT2
{
public:
	CT3(void);
	CT3(double u, double v, double w);
	friend CT3 operator + (const CT3 &t0, const CT3 &t1);//‘ÀÀ„∑˚÷ÿ‘ÿ
	friend CT3 operator - (const CT3 &t0, const CT3 &t1);
	friend CT3 operator * (const CT3 &t, double scalar);
	friend CT3 operator * (double scalar, const CT3 &t);
	friend CT3 operator / (const CT3 &t, double scalar);
	virtual ~CT3(void);
public:
	double w;
};

