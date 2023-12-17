
// TestView.cpp: CTestView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PI 3.1415926//PI的宏定义
#define ROUND(d) int(d + 0.5)//四舍五入宏定义

// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_GRAPH_ANIMATION, &CTestView::OnGraphDraw)
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView() noexcept
{
	// TODO: 在此处添加构造代码
	i = 0;
	p[0].c = CRGB(1.0, 0.0, 0.0);
	p[1].c = CRGB(0.0, 1.0, 0.0);
	p[2].c = CRGB(0.0, 0.0, 1.0);
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestView 绘图

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

// CTestView 打印

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTestView 诊断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView 消息处理程序


void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CLine* pLine = new CLine;
	CDC* pDC = GetDC();
	if (i < 3)
	{
		p[i].x = point.x;
		p[i].y = point.y;
		pDC->Ellipse(ROUND(p[i].x - 5), ROUND(p[i].y - 5), ROUND(p[i].x + 5), ROUND(p[i].y + 5));
		i++;
	}
	if (i >= 2)
	{
		pLine->MoveTo(pDC, CPoint2(p[i - 2].x, p[i - 2].y, p[i - 2].c));
		pLine->LineTo(pDC, CPoint2(p[i - 1].x, p[i - 1].y, p[i - 1].c));
	}
	delete pLine;
	ReleaseDC(pDC);
	CView::OnLButtonDown(nFlags, point);
}


void CTestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnLButtonUp(nFlags, point);
}


void CTestView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC* pDC = GetDC();
	CLine* pLine = new CLine;
	if (i > 2)
	{
		if (p[0].x - 5 < point.x && point.x < p[0].x + 5 && p[0].y - 5 < point.y && point.y < p[0].y + 5)
		{
			pLine->MoveTo(pDC, CPoint2(p[2].x, p[2].y, p[2].c));
			pLine->LineTo(pDC, CPoint2(p[0].x, p[0].y, p[0].c));
		}
	}
	delete pLine;
	ReleaseDC(pDC);
	CView::OnMouseMove(nFlags, point);
}


void CTestView::OnGraphDraw()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(CString("请按下鼠标左键绘制三角形！"), CString("提示"), MB_ICONEXCLAMATION | MB_OK);
	RedrawWindow();
	i = 0;
}
