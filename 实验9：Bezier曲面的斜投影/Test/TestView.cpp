
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


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_GRAPH_ANIMATION, &CTestView::OnGraphAnimation)
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView() noexcept
{
	// TODO: 在此处添加构造代码
	ReadPoint();
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
	CRect rect;//定义客户区矩形
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//设置视区范围,x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//客户区中心为原点
	DrawObject(pDC);//绘制图形	
}

void CTestView::ReadPoint(void)//读入控制多边形顶点
{
	P[0][0].x = 20;   P[0][0].y = -50;   P[0][0].z = 200;
	P[0][1].x = 0;    P[0][1].y = 70; P[0][1].z = 150;
	P[0][2].x = -130; P[0][2].y = 70; P[0][2].z = 50;
	P[0][3].x = -250; P[0][3].y = 20;  P[0][3].z = 0;
	P[1][0].x = 100;  P[1][0].y = 70; P[1][0].z = 150;
	P[1][1].x = 30;   P[1][1].y = 70; P[1][1].z = 100;
	P[1][2].x = -40;  P[1][2].y = 70; P[1][2].z = 50;
	P[1][3].x = -110; P[1][3].y = 70; P[1][3].z = 0;
	P[2][0].x = 280;  P[2][0].y = 60;  P[2][0].z = 140;
	P[2][1].x = 110;  P[2][1].y = 90; P[2][1].z = 80;
	P[2][2].x = 0;    P[2][2].y = 100; P[2][2].z = 30;
	P[2][3].x = -100; P[2][3].y = 120; P[2][3].z = -50;
	P[3][0].x = 350;  P[3][0].y = 0;  P[3][0].z = 150;
	P[3][1].x = 200;  P[3][1].y = 120; P[3][1].z = 50;
	P[3][2].x = 50;   P[3][2].y = 170; P[3][2].z = 0;
	P[3][3].x = 0;    P[3][3].y = 70; P[3][3].z = -70;
}

void CTestView::DrawObject(CDC* pDC)//绘制图形
{
	CBezierPatch patch;
	int n = 2;
	patch.ReadControlPoint(P, n);
	patch.DrawCurvedPatch(pDC);
	patch.DrawControlGrid(pDC);
	patch.MarkControlGrid(pDC);
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
void CTestView::OnGraphAnimation()
{
	// TODO: 在此添加命令处理程序代码
	
}