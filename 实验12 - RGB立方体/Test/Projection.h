#pragma once
#include "P3.h"

class CProjection
{
public:
	CProjection(void);
	virtual ~CProjection(void);
	void SetEye(double R);//�����ӵ�
	CP3 GetEye(void);//��ȡ�ӵ�
	CP2 ObliqueProjection(CP3 WorldPoint);//бͶӰ
	CP2 OrthogonalProjection(CP3 WorldPoint);//����ͶӰ
	CP2 PerspectiveProjection(CP3 WorldPoint);//͸��ͶӰ
private:
	CP3 EyePoint;//�ӵ�
	double R, d;//�Ӿ����Ӿ�
};

