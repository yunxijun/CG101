
// TestView.h: CTestView 类的接口
//

#pragma once
#include "Transform3.h"
#include "Triangle.h"
#include "Cube.h"
#include"Projection.h"

class CTestView : public CView
{
protected: // 仅从序列化创建
	CTestView() noexcept;
	DECLARE_DYNCREATE(CTestView)

// 特性
public:
	CTestDoc* GetDocument() const;

// 操作
public:
	void DoubleBuffer(CDC* pDC);//双缓冲绘图
	void DrawObject(CDC* pDC);//绘制图形
	void BubbleSort(void);//冒泡排序
	double GetMaxDepth(double* M, int n);//面的最大深度
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CP3 GPoint[8];//总点数
	CFacet GFacet[6];//总面数	
	CCube cube;//立方体对象
	CTransform3 transform;//变换对象
	CProjection projection;//投影
	double Alpha, Beta;//x方向旋转α角,y方向旋转β角
	BOOL bPlay;//动画开关
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGraphAnimation();
	afx_msg void OnUpdateGraphAnimation(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // TestView.cpp 中的调试版本
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

