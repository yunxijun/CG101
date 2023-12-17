
// MFCBasicView.cpp: CMFCBasicView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCBasic.h"
#endif

#include "MFCBasicDoc.h"
#include "MFCBasicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasicView
					
IMPLEMENT_DYNCREATE(CMFCBasicView, CView)

BEGIN_MESSAGE_MAP(CMFCBasicView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMFCBasicView 构造/析构

CMFCBasicView::CMFCBasicView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCBasicView::~CMFCBasicView()
{
}

BOOL CMFCBasicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCBasicView 绘图

void CMFCBasicView::OnDraw(CDC* /*pDC*/)
{
	CMFCBasicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCBasicView 打印

BOOL CMFCBasicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCBasicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCBasicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCBasicView 诊断

#ifdef _DEBUG
void CMFCBasicView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCBasicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCBasicDoc* CMFCBasicView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCBasicDoc)));
	return (CMFCBasicDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCBasicView 消息处理程序


void CMFCBasicView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	P0 = point;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCBasicView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC* pDC = GetDC();
	CPen pen(PS_SOLID, 5, RGB(255, 0, 0));
	pDC->SelectObject(&pen);		
	P1 = point;
/*	pDC->MoveTo(P0);
	pDC->LineTo(P1);	*/	
	//pDC->Rectangle(P0.x, P0.y, P1.x, P1.y);
	CBrush brush(RGB(0, 255, 0));
	pDC->SelectObject(&brush);
	pDC->Ellipse(P0.x, P0.y, P1.x, P1.y);
	ReleaseDC(pDC);
	CView::OnLButtonUp(nFlags, point);
}
