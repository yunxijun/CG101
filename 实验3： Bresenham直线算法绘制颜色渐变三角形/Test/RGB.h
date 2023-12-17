#pragma once

class CRGB
{
public:
	CRGB(void);
	CRGB(double red, double green, double blue);
	virtual ~CRGB(void);
	friend CRGB operator + (const CRGB &c0, const CRGB &c1);//���������
	friend CRGB operator - (const CRGB &c0, const CRGB &c1);
	friend CRGB operator * (const CRGB &c0, const CRGB &c1);
	friend CRGB operator * (const CRGB &c, double scalar);
	friend CRGB operator * (double scalar, const CRGB &c);
	friend CRGB operator / (const CRGB &c1, double scalar);
	friend CRGB operator += (CRGB &c0, CRGB &c1);
	friend CRGB operator -= (CRGB &c0, CRGB &c1);
	friend CRGB operator *= (CRGB &c0, CRGB &c1);
	friend CRGB operator /= (CRGB &c, double scalar);
	void   Normalize(void);	//��ɫ������һ����[0,1]����
public:
	double red;//��ɫ����
	double green;//��ɫ����
	double blue;//��ɫ����
};

