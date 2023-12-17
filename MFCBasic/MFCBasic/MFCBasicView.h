
// MFCBasicView.h: CMFCBasicView 类的接口
//

#pragma once


class CMFCBasicView : public CView
{
protected: // 仅从序列化创建
	CMFCBasicView() noexcept;
	DECLARE_DYNCREATE(CMFCBasicView)

// 特性
public:
	CMFCBasicDoc* GetDocument() const;

// 操作
public:

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
	virtual ~CMFCBasicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPoint P0;
	CPoint P1;
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
 
#ifndef _DEBUG  // MFCBasicView.cpp 中的调试版本
inline CMFCBasicDoc* CMFCBasicView::GetDocument() const
   { return reinterpret_cast<CMFCBasicDoc*>(m_pDocument); }
#endif

