#pragma once
#include"resource.h"

class CTexture
{
public:
	CTexture(void);
	virtual~CTexture(void);
	void PrepareBitmap(void);//׼��λͼ
	void DeleteObject(void);//�ͷ�λͼ
public:
	BYTE* image;
	BITMAP bmp;//BITMAP�ṹ�����
};

