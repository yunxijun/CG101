#pragma once
#include "P2.h"
class CTransform2
{
public:
	CTransform2(void);
	virtual ~CTransform2(void);
	void SetMatrix(CP2* P, int ptNumber);//设置二维顶点数组
	void Identity(void);//单位矩阵
	void Translate(double tx, double ty);//平移变换
	void Scale(double sx, double sy);//比例变换
	void Scale(double sx, double sy, CP2 p);//相对于任意点的比例变换
	void Rotate(double beta);//旋转变换矩阵
	void Rotate(double beta, CP2 p);//相对于任意点的旋转变换
	void ReflectOrg(void);//关于原点反射变换
	void ReflectX(void);//关于X轴反射变换
	void ReflectY(void);//关于Y轴反射变换
	void Shear(double b, double c);//错切变换
	void MultiplyMatrix(void);//矩阵相乘
private:
	double T[3][3];//变换矩阵
	CP2* P;//顶点数组
	int  ptNumber;//顶点个数
};

