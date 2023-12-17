#pragma once
class CSphere
{
public:
	CSphere(void);
	virtual ~CSphere(void);
	void Draw(CDC* pDC);//绘制球体
public:
	int R;//球体半径
	CPoint CenterPoint;//中心点
};

