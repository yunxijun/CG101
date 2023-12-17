#pragma once
#include "P3.h"

class CProjection
{
public:
	CProjection(void);
	virtual ~CProjection(void);
	void SetEye(double R);//设置视点
	CP3 GetEye(void);//读取视点
	CP2 ObliqueProjection(CP3 WorldPoint);//斜投影
	CP2 OrthogonalProjection(CP3 WorldPoint);//正交投影
	CP2 PerspectiveProjection(CP3 WorldPoint);//透视投影
private:
	CP3 EyePoint;//视点
	double R, d;//视径和视距
};

