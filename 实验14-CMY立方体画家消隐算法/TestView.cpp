
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
#define ROUND(d) int(d + 0.5)//四舍五入宏定义

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
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView() noexcept
{
	// TODO: 在此处添加构造代码
	bPlay = FALSE;
	int nEdge = 500;
	cube.ReadPoint();
	cube.ReadFacet();
	transform.SetMatrix(cube.P, 8);
	transform.Scale(nEdge, nEdge, nEdge);//比例变换
	transform.Translate(-nEdge / 2, -nEdge / 2, -nEdge / 2);//平移变换
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
	memDC.FillSolidRect(rect, pDC->GetBkColor());//设置客户区背景色
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
	for(int j = 0; j < 8; j++)//点表赋值
		GPoint[j] = cube.P[j];
	for(int j = 0; j < 6; j++)//面表赋值
	{
		GFacet[j].Number = cube.F[j].Number;
		for (int k = 0; k < GFacet[j].Number; k++)
			GFacet[j].Index[k] = cube.F[j].Index[k];
	}
	double zDepth[4];//表面的4个顶点深度
	for(int i = 0; i < 6; i++)
	{
		for(int nPoint = 0; nPoint < GFacet[i].Number; nPoint++)//顶点循环
			zDepth[nPoint] = projection.PerspectiveProjection3(GPoint[GFacet[i].Index[nPoint]]).z;// 表面顶点的深度
		GFacet[i].fMaxDepth = GetMaxDepth(zDepth, GFacet[i].Number);//计算表面的最大深度
	}
	BubbleSort();//面表排序
	CP3 ScreenPoint[4], temp;
	for (int i = 0; i < 6; i++)
	{
		for (int nPoint = 0; nPoint < GFacet[i].Number; nPoint++)//顶点循环
			ScreenPoint[nPoint] = projection.PerspectiveProjection3(GPoint[GFacet[i].Index[nPoint]]);
		CTriangle* pFill = new CTriangle;//申请内存
		pFill->SetPoint(ScreenPoint[0], ScreenPoint[2], ScreenPoint[3]);//填充三角形
		pFill->GouraudShader(pDC);
		pFill->SetPoint(ScreenPoint[0], ScreenPoint[1], ScreenPoint[2]);//填充三角形
		pFill->GouraudShader(pDC);
		delete pFill;//撤销内存
		pDC->MoveTo(ROUND(ScreenPoint[0].x), ROUND(ScreenPoint[0].y));
		pDC->LineTo(ROUND(ScreenPoint[1].x), ROUND(ScreenPoint[1].y));
		pDC->LineTo(ROUND(ScreenPoint[2].x), ROUND(ScreenPoint[2].y));
		pDC->LineTo(ROUND(ScreenPoint[3].x), ROUND(ScreenPoint[3].y));
		pDC->LineTo(ROUND(ScreenPoint[0].x), ROUND(ScreenPoint[0].y));
	}
}

void CTestView::BubbleSort(void)//冒泡排序
{
	//对一维数组F进行冒泡排序
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5 - i; j++)
		{
			if(GFacet[j].fMaxDepth < GFacet[j + 1].fMaxDepth)
			{
				CFacet Temp;
				Temp = GFacet[j];
				GFacet[j] = GFacet[j + 1];
				GFacet[j + 1] = Temp;
			}
		}
	}
}

double CTestView::GetMaxDepth(double* D, int n)//计算表面的最大深度
{
	double MaxDepth = D[0];
	for(int i = 1; i < n; i++)
		if(MaxDepth < D[i])
			MaxDepth = D[i];
	return MaxDepth;
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
	Alpha = 5;
	transform.RotateX(Alpha);
	Beta = 5;
	transform.RotateY(Beta);
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
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
			transform.RotateX(Alpha);
			break;
		case VK_DOWN:
			Alpha = 5;
			transform.RotateX(Alpha);
			break;
		case VK_LEFT:
			Beta = -5;
			transform.RotateY(Beta);
			break;
		case VK_RIGHT:
			Beta = 5;
			transform.RotateY(Beta);
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
	if (bPlay)
		SetTimer(1, 150, NULL);
	else
		KillTimer(1);
}

void CTestView::OnUpdateGraphAnimation(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (bPlay)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
