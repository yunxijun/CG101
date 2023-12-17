
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
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GRAPH_ANIMATION, &CTestView::OnGraphAnimation)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_ANIMATION, &CTestView::OnUpdateGraphAnimation)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView() noexcept
{
	// TODO: 在此处添加构造代码
	bPlay = FALSE;
	NumofObject = 4;
	int a = 500;//长度
	int b = 60;//高度
	int c = 300;//厚度
	int e = 160;//收缩宽度
	int d = 120;//交叉头
	CRGB red(1.0, 0.0, 0.0);//红色
	CRGB green(0.0, 1.0, 0.0);//绿色
	CRGB blue(0.0, 0.0, 1.0);//蓝色
	CRGB yellow(1.0, 1.0, 0.0);//黄色
	bar[0].SetParameter(a, b, c, green, red);//顶面长方条
	bar[1].SetParameter(a, b, c, red, green);//底面长方条
	bar[2].SetParameter(a, b, e, blue, yellow);//左面长方条
	bar[3].SetParameter(a, b, e, yellow, blue);//右面长方条
	for (int i = 0; i < NumofObject; i++)
	{
		bar[i].ReadPoint();
		bar[i].ReadFacet();
		transform[i].SetMatrix(bar[i].P, 8);
	}
	transform[0].Translate(0, d + b / 2, 0);//顶面长方条位置
	transform[1].Translate(0, -d - b / 2, 0);//底面长方条位置
	transform[2].RotateZ(90);//左面长方条
	transform[2].Translate(-d - b / 2, 0, 0);
	transform[3].RotateZ(90);//右面长方条
	transform[3].Translate(d + b / 2, 0, 0);
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
	DoubleBuffer(pDC);//绘制图形
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
void CTestView::DoubleBuffer(CDC* pDC)//双缓冲绘图
{
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	CDC memDC;//声明内存DC
	memDC.CreateCompatibleDC(pDC);//创建一个与显示DC兼容的内存DC
	CBitmap NewBitmap, *pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//创建兼容内存位图 
	pOldBitmap = memDC.SelectObject(&NewBitmap);//将兼容位图选入内存DC
	//memDC.FillSolidRect(rect, pDC->GetBkColor());//设置客户区背景色
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	memDC.SetMapMode(MM_ANISOTROPIC);//内存DC自定义坐标系
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	DrawObject(&memDC);//绘制图形
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY); //将内存DC中的位图拷贝到显示DC
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();
}

void CTestView::DrawObject(CDC* pDC)//绘制图形
{
	CZBuffer* pZBuffer = new CZBuffer;//申请内存
	pZBuffer->InitialDepthBuffer(1000, 1000, 1000);//初始化深度缓冲器
	for (int i = 0; i < NumofObject; i++)
		bar[i].Draw(pDC, pZBuffer);	
	delete pZBuffer;//释放内存
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!bPlay)
	{
		switch (nChar)
		{
		case VK_UP:
			Alpha = -5;
			for (int i = 0; i < NumofObject; i++)
				transform[i].RotateX(Alpha);
			break;
		case VK_DOWN:
			Alpha = 5;
			for (int i = 0; i < NumofObject; i++)
				transform[i].RotateX(Alpha);
			break;
		case VK_LEFT:
			Beta = -5;
			for (int i = 0; i < NumofObject; i++)
				transform[i].RotateY(Beta);
			break;
		case VK_RIGHT:
			Beta = 5;
			for (int i = 0; i < NumofObject; i++)
				transform[i].RotateY(Beta);
			break;
		default:
			break;
		}
		Invalidate(FALSE);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnGraphAnimation()
{
	// TODO: 在此添加命令处理程序代码
	bPlay = !bPlay;
	if (bPlay)//设置定时器
		SetTimer(1, 150, NULL);
	else
		KillTimer(1);
}

void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Alpha = 5;	Beta = 5;
	for (int i = 0; i < NumofObject; i++)
	{
		transform[i].RotateX(Alpha);
		transform[i].RotateY(Beta);
	}
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}

void CTestView::OnUpdateGraphAnimation(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (bPlay)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

BOOL CTestView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	return TRUE;
}