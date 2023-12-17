
// TestView.h: CTestView 类的接口
//

#pragma once
#include "Transform3.h"
#include "Revolution.h"
#include"Texture.h"

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
	void DoubleBuffer(CDC* pDC);//双缓冲
	void DrawObject(CDC* pDC);//绘制图形
	void InitializeLightingScene(void);//初始化光照场景
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
	CP2 P0[4];//第0段二维点
	CP2 P1[4];//第1段二维点
	CP2 P2[4];//第2段二维点
	CP2 P3[4];//第3段二维点
	CP3 V0[4];//第0段三维点
	CP3 V1[4];//第1段三维点
	CP3 V2[4];//第2段三维点
	CP3 V3[4];//第3段三维点
	double Alpha, Beta;
	CRevolution revo0, revo1, revo2, revo3;
	CTransform3 tran0, tran1, tran2, tran3;
	BOOL bPlay;//动画按钮
	int	nLightSourceNumber;//光源数量
	CLighting* pLight;//光照环境
	CMaterial* pMaterial;//物体材质
	CTexture texture;//纹理
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGraphAnimation();
	afx_msg void OnUpdateGraphAnimation(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // TestView.cpp 中的调试版本
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

