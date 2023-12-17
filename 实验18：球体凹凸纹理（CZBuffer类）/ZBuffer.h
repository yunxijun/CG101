#pragma once
#include "Point3.h"
#include "Lighting.h"//Blinn-Phongģ��

class CZBuffer
{
public:
	CZBuffer(void);
	virtual ~CZBuffer(void);
	void InitialDepthBuffer(int nWidth, int nHeight, double zDepth);//��ʼ����Ȼ�����
	void SetPoint(CP3 P0, CP3 P1, CP3 P2, CVector3 N0, CVector3 N1, CVector3 N2);// �����γ�ʼ��
	void PhongShader(CDC* pDC, CP3 ViewPoint, CLighting* pLight, CMaterial* pMaterial);//�⻬��ɫ
private:
	void SortVertex(void);//��������
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//�߱��
	CVector3 LinearInterp(double t, double coorStart, double coorEnd, CVector3 normalStart, CVector3 normalEnd);//�������Բ�ֵ
protected:
	CP3 P0, P1, P2;//�����εĸ���������
	CPoint3 point0, point1, point2;//�����ε�������������
	CPoint2* SpanLeft; //��ȵ���������־
	CPoint2* SpanRight;//��ȵ��յ������־
	int nIndex;//��¼ɨ��������
	double** zBuffer;//��Ȼ�����
	int nWidth, nHeight;//�����������߶�
};

