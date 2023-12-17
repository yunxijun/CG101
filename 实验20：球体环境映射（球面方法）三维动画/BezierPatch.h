#pragma once
#include"Mesh.h"
#include"Projection.h"
#include"ZBuffer.h"

class CBezierPatch
{
public:
	CBezierPatch(void);
	virtual ~CBezierPatch(void);
	void ReadControlPoint(CP3 CtrPt[4][4], int ReNumber);//����16�����Ƶ�͵ݹ����
	void SetScene(CLighting* pLight, CMaterial* pMaterial);//���ó���
	void SetTexture(CTexture* pTexture);
	void DrawCurvedPatch(CDC* pDC, CZBuffer* pZBuffer);//��������
	void DrawControlGrid(CDC* pDC);//���ƿ�������
private:
	void Recursion(CDC* pDC, CZBuffer* pZBuffer, int ReNumber, CMesh Mesh);//�ݹ麯��
	void Tessellation(CMesh Mesh);//ϸ�ֺ���
	void DrawFacet(CDC* pDC, CZBuffer* pZBuffer);//�����ı�������
	void LeftMultiplyMatrix(double M[4][4], CP3 P[4][4]);//��˶������
	void RightMultiplyMatrix(CP3 P[4][4], double M[4][4]);//�ҳ˶������
	void TransposeMatrix(double M[4][4]);//ת�þ���
private:
	int ReNumber;//�ݹ����
	CP3 CtrPt[4][4];//�����16�����Ƶ�
	CP3 quadrP[4];//�ı��εĶ���
	CProjection projection;//ͶӰ
	CLighting* pLight;//����
	CMaterial* pMaterial;//����
	CTexture* pTexture;
};

