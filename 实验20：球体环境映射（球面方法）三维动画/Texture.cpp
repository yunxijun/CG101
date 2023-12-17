#include "pch.h"
#include "Texture.h"

CTexture::CTexture(void)
{
	image = NULL;
}

CTexture::~CTexture(void)
{
}

void CTexture::PrepareBitmap(void)//׼��λͼ
{
	CBitmap NewBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP1);
	NewBitmap.GetBitmap(&bmp);//��CBitmap����Ϣ���浽Bitmap�ṹ����
	int nbytesize = bmp.bmWidthBytes * bmp.bmHeight;
	image = new BYTE[nbytesize];
	NewBitmap.GetBitmapBits(nbytesize, (LPVOID)image);
}

void CTexture::DeleteObject(void)//�ͷ�λͼ
{
	if(NULL != image)
		delete []image;
}