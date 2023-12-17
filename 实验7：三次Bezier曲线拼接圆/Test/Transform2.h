#pragma once
#include "P2.h"
class CTransform2
{
public:
	CTransform2(void);
	virtual ~CTransform2(void);
	void SetMatrix(CP2* P, int ptNumber);//���ö�ά��������
	void Identity(void);//��λ����
	void Translate(double tx, double ty);//ƽ�Ʊ任
	void Scale(double sx, double sy);//�����任
	void Scale(double sx, double sy, CP2 p);//����������ı����任
	void Rotate(double beta);//��ת�任����
	void Rotate(double beta, CP2 p);//�������������ת�任
	void ReflectOrg(void);//����ԭ�㷴��任
	void ReflectX(void);//����X�ᷴ��任
	void ReflectY(void);//����Y�ᷴ��任
	void Shear(double b, double c);//���б任
	void MultiplyMatrix(void);//�������
private:
	double T[3][3];//�任����
	CP2* P;//��������
	int  ptNumber;//�������
};

