#include "pch.h"
#include "Cube.h"

CCube::CCube(void)
{

}

CCube::~CCube(void)
{

}

CP3* CCube::GetVertexArrayName(void)//���������
{
	return P;
}

void CCube::ReadPoint(void)//���
{
	P[0].x = 0, P[0].y = 0, P[0].z = 0; P[0].c = CRGB(0.0, 0.0, 0.0);
	P[1].x = 1, P[1].y = 0, P[1].z = 0; P[1].c = CRGB(1.0, 0.0, 0.0);
	P[2].x = 1, P[2].y = 1, P[2].z = 0; P[2].c = CRGB(1.0, 1.0, 0.0);
	P[3].x = 0, P[3].y = 1, P[3].z = 0; P[3].c = CRGB(0.0, 1.0, 0.0);
	P[4].x = 0, P[4].y = 0, P[4].z = 1; P[4].c = CRGB(0.0, 0.0, 1.0);
	P[5].x = 1, P[5].y = 0, P[5].z = 1; P[5].c = CRGB(1.0, 0.0, 1.0);
	P[6].x = 1, P[6].y = 1, P[6].z = 1; P[6].c = CRGB(1.0, 1.0, 1.0);
	P[7].x = 0, P[7].y = 1, P[7].z = 1; P[7].c = CRGB(0.0, 1.0, 1.0);
}

void CCube::ReadFacet(void)//���
{
	F[0].Number = 4; F[0].Index[0] = 4; F[0].Index[1] = 5; F[0].Index[2] = 6; F[0].Index[3] = 7;//ǰ��
	F[1].Number = 4; F[1].Index[0] = 0; F[1].Index[1] = 3; F[1].Index[2] = 2; F[1].Index[3] = 1;//����
	F[2].Number = 4; F[2].Index[0] = 0; F[2].Index[1] = 4; F[2].Index[2] = 7; F[2].Index[3] = 3;//����
	F[3].Number = 4; F[3].Index[0] = 1; F[3].Index[1] = 2; F[3].Index[2] = 6; F[3].Index[3] = 5;//����
	F[4].Number = 4; F[4].Index[0] = 2; F[4].Index[1] = 3; F[4].Index[2] = 7; F[4].Index[3] = 6;//����
	F[5].Number = 4; F[5].Index[0] = 0; F[5].Index[1] = 1; F[5].Index[2] = 5; F[5].Index[3] = 4;//����
}

void CCube::Draw(CDC* pDC)
{
	CP2 ScreenPoint[4];//��Ļ��ά��
	CP3 ViewPoint = projection.GetEye();//�ӵ�
	CTriangle* pFill = new CTriangle;//�����ڴ�
	for (int nFacet = 0; nFacet < 6; nFacet++)//��ѭ��
	{
		CP3 ViewPoint = projection.GetEye();//�ӵ�
		CVector3 ViewVector(P[F[nFacet].Index[0]], ViewPoint);// ���������
		ViewVector = ViewVector.Normalize();//��������λ��
		CVector3 Vector01(P[F[nFacet].Index[0]], P[F[nFacet].Index[1]]);//������
		CVector3 Vector02(P[F[nFacet].Index[0]], P[F[nFacet].Index[2]]);
		CVector3 FacetNormal = CrossProduct(Vector01, Vector02);//�淨����
		FacetNormal = FacetNormal.Normalize();
		if (DotProduct(ViewVector, FacetNormal) >= 0)//�����޳��㷨
		{
			for (int nPoint = 0; nPoint < 4; nPoint++)
			{
				ScreenPoint[nPoint] = projection.PerspectiveProjection(P[F[nFacet].Index[nPoint]]);
			}
			pFill->SetPoint(ScreenPoint[0], ScreenPoint[2], ScreenPoint[3]);//��������
			pFill->GouraudShader(pDC);
			pFill->SetPoint(ScreenPoint[0], ScreenPoint[1], ScreenPoint[2]);//��������			
			pFill->GouraudShader(pDC);
		}
	}
	delete pFill;//�ͷ��ڴ�
}