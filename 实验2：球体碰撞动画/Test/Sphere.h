#pragma once
class CSphere
{
public:
	CSphere(void);
	virtual ~CSphere(void);
	void Draw(CDC* pDC);//��������
public:
	int R;//����뾶
	CPoint CenterPoint;//���ĵ�
};

