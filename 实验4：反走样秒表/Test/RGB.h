#pragma once
class CRGB
{
public:
	CRGB(void);
	CRGB(double red, double green, double blue);
	~CRGB(void);
	friend CRGB operator+(const CRGB &c1, const CRGB &c2);//运算符重载
	friend CRGB operator-(const CRGB &c1, const CRGB &c2);
	friend CRGB operator*(const CRGB &c1, const CRGB &c2);
	friend CRGB operator*(const CRGB &c1, double scalar);
	friend CRGB operator*(double scalar, const CRGB &c);
	friend CRGB operator/(const CRGB &c1, double scalar);
	friend CRGB operator+=(CRGB &c1, CRGB &c2);
	friend CRGB operator-=(CRGB &c1, CRGB &c2);
	friend CRGB operator*=(CRGB &c1, CRGB &c2);
	friend CRGB operator/=(CRGB &c1, double scalar);
	void   Normalize();	//颜色分量归一化到[0,1]区间
public:
	double red;//红色分量
	double green;//绿色分量
	double blue;//蓝色分量
};

