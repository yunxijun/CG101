
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
#define PI 3.1415926
#define ROUND(d) int (d + 0.5)

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
	ON_COMMAND(ID_GRAPH_ANIMATION, &CTestView::OnGraphAnimation)
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView() noexcept
{
	// TODO: 在此处添加构造代码
	r = 220;//表盘的内半径
	bPlay = FALSE;
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
	SetTimer(1, 1000, NULL);
	DoubleBuffer(pDC);
}

void CTestView::DoubleBuffer(CDC* pDC)//双缓冲绘图
{
	CRect rect;
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//客户区中心为原点
	CDC memDC;//内存缓冲区
	memDC.CreateCompatibleDC(pDC);//建立与屏幕pDC兼容的memDC 
	CBitmap NewBitmap, *pOldBitmap;//内存中承载图像的临时位图
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//创建兼容位图
	pOldBitmap = memDC.SelectObject(&NewBitmap); //将兼容位图选入memDC
	memDC.FillSolidRect(rect, pDC->GetBkColor());//按原来背景填充客户区，否则是黑色
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC自定义坐标系
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	DrawClock(&memDC);//绘制秒针钟表
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);//将memDC缓冲区中的图形拷贝到pDC缓冲区
	memDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图
	memDC.DeleteDC();//删除memDC
}

void CTestView::DrawClock(CDC* pDC) //绘制反走样秒针
{
	DrawPlate(pDC);
	CTime time = CTime::GetCurrentTime();
	//绘制秒针
	Tsecond = time.GetSecond();
	Tangle = Tsecond * 2 * PI / 60.0;
	p1.x = ROUND(r  * sin(Tangle));
	p1.y = ROUND(r  * cos(Tangle));
	CALine aline;
	aline.MoveTo(pDC, CP2(0.0, 0.0));
	aline.LineTo(pDC, p1);
}

void CTestView::DrawPlate(CDC* pDC)//绘制表盘
{
	pDC->Ellipse(- r,  - r, + r, + r);//绘制圆内框
	pDC->Ellipse(- 10, - 10, + 10,+ 10);//绘制表芯
	for (int i = 1; i <= 60; i++)//输出表的时钟值
	{
		CString str;
		str.Format(CString("%d"), i);
		CSize size;
		size = pDC->GetTextExtent(str, str.GetLength());
		Tangle = i * 2 * PI / 60.0;
		CP2 p;//计算时钟值放置位置
		p.x = p0.x - (size.cx / 2) + ROUND((r - 15) * sin(Tangle));
		p.y = p0.y + (size.cy / 2) + ROUND((r - 15) * cos(Tangle));
		pDC->TextOut(ROUND(p.x), ROUND(p.y), str);
	}
	//输出表盘顶端文字
	pDC->SetBkColor(RGB(255, 255, 255));
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->TextOut(-58, 300, CString("反走样秒表"));
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


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}

void CTestView::OnGraphAnimation()
{
	// TODO: 在此添加命令处理程序代码	
}
