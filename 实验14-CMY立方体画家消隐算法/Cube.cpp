#include "pch.h"
#include "Cube.h"

CCube::CCube(void)
{

}

CCube::~CCube(void)
{
}

void CCube::ReadPoint(void)//读入点表
{
	P[0].x = 0, P[0].y = 0, P[0].z = 0; P[0].c = CRGB(1.0, 1.0, 1.0);
	P[1].x = 1, P[1].y = 0, P[1].z = 0; P[1].c = CRGB(0.0, 1.0, 1.0);
	P[2].x = 1, P[2].y = 1, P[2].z = 0; P[2].c = CRGB(0.0, 0.0, 1.0);
	P[3].x = 0, P[3].y = 1, P[3].z = 0; P[3].c = CRGB(1.0, 0.0, 1.0);
	P[4].x = 0, P[4].y = 0, P[4].z = 1; P[4].c = CRGB(1.0, 1.0, 0.0);
	P[5].x = 1, P[5].y = 0, P[5].z = 1; P[5].c = CRGB(0.0, 1.0, 0.0);
	P[6].x = 1, P[6].y = 1, P[6].z = 1; P[6].c = CRGB(0.0, 0.0, 0.0);
	P[7].x = 0, P[7].y = 1, P[7].z = 1; P[7].c = CRGB(1.0, 0.0, 0.0);
}

void CCube::ReadFacet(void)//读入面表
{
	F[0].Number = 4; F[0].Index[0] = 4; F[0].Index[1] = 5; F[0].Index[2] = 6; F[0].Index[3] = 7;//前面
	F[1].Number = 4; F[1].Index[0] = 0; F[1].Index[1] = 3; F[1].Index[2] = 2; F[1].Index[3] = 1;//后面
	F[2].Number = 4; F[2].Index[0] = 0; F[2].Index[1] = 4; F[2].Index[2] = 7; F[2].Index[3] = 3;//左面
	F[3].Number = 4; F[3].Index[0] = 1; F[3].Index[1] = 2; F[3].Index[2] = 6; F[3].Index[3] = 5;//右面
	F[4].Number = 4; F[4].Index[0] = 2; F[4].Index[1] = 3; F[4].Index[2] = 7; F[4].Index[3] = 6;//顶面
	F[5].Number = 4; F[5].Index[0] = 0; F[5].Index[1] = 1; F[5].Index[2] = 5; F[5].Index[3] = 4;//底面
}