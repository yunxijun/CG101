#include "pch.h"
#include "RGB.h"

CRGB::CRGB(void)
{
	red = 1.0;
	green = 1.0;
	blue = 1.0;
}

CRGB::CRGB(double red, double green, double blue)//重载构造函数
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

CRGB::~CRGB(void)
{

}

CRGB operator + (const CRGB &c0, const CRGB &c1)//"+"运算符重载
{
	CRGB color;
	color.red = c0.red + c1.red;
	color.green = c0.green + c1.green;
	color.blue = c0.blue + c1.blue;
	return color;
}

CRGB operator - (const CRGB &c0, const CRGB &c1)//"-"运算符重载
{
	CRGB color;
	color.red = c0.red - c1.red;
	color.green = c0.green - c1.green;
	color.blue = c0.blue - c1.blue;
	return color;
}

CRGB operator * (const CRGB &c0, const CRGB &c1)//"*"运算符重载
{
	CRGB color;
	color.red = c0.red * c1.red;
	color.green = c0.green * c1.green;
	color.blue = c0.blue * c1.blue;
	return color;
}

CRGB operator * (const CRGB &c, double scalar)//"*"运算符重载
{
	CRGB color;
	color.red = scalar * c.red;
	color.green = scalar * c.green;
	color.blue = scalar * c.blue;
	return color;
}

CRGB operator * (double scalar, const CRGB &c)//"*"运算符重载
{
	CRGB color;
	color.red = scalar * c.red;
	color.green = scalar * c.green;
	color.blue = scalar * c.blue;
	return color;
}

CRGB operator / (const CRGB &c, double scalar)//"/"运算符重载
{
	CRGB color;
	color.red = c.red / scalar;
	color.green = c.green / scalar;
	color.blue = c.blue / scalar;
	return color;
}

CRGB operator += (CRGB &c0, CRGB &c1)//"+="运算符重载
{
	c0.red += c1.red;
	c0.green += c1.green;
	c0.blue += c1.blue;
	return c0;
}

CRGB operator -= (CRGB &c0, CRGB &c1)//"-="运算符重载
{
	c0.red -= c1.red;
	c0.green -= c1.green;
	c0.blue -= c1.blue;
	return c0;
}

CRGB operator *= (CRGB &c0, CRGB &c1)//"*="运算符重载
{
	c0.red *= c1.red;
	c0.green *= c1.green;
	c0.blue *= c1.blue;
	return c0;
}

CRGB operator /= (CRGB &c, double scalar)//"/="运算符重载
{
	c.red /= scalar;
	c.green /= scalar;
	c.blue /= scalar;
	return c;
}

void CRGB::Normalize(void)//颜色归一化处理
{
	red = (red < 0.0) ? 0.0 : ((red > 1.0) ? 1.0 : red);
	green = (green < 0.0) ? 0.0 : ((green > 1.0) ? 1.0 : green);
	blue = (blue < 0.0) ? 0.0 : ((blue > 1.0) ? 1.0 : blue);
}
