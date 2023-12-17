
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
	ON_UPDATE_COMMAND_UI(ID_GRAPH_ANIMATION, &CTestView::OnUpdateGraphAnimation)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView() noexcept
{
	// TODO: 在此处添加构造代码
	bPlay = FALSE;
	double m = 0.5523;
	double R = 300, r = 120;
	Alpha = 30;
	//外第1段
	P0[0] = CP2(R, -r);
	P0[1] = CP2(R + m * r, -r);
	P0[2] = CP2(R + r, -m * r);
	P0[3] = CP2(R + r, 0);
	//外第2段	
	P1[0] = CP2(R + r, 0);
	P1[1] = CP2(R + r, m * r);
	P1[2] = CP2(R + m * r, r);
	P1[3] = CP2(R, r);
	//内第1段
	P2[0] = CP2(R, r);
	P2[1] = CP2(R - m * r, r);
	P2[2] = CP2(R - r, m * r);
	P2[3] = CP2(R - r, 0); 
	//内第2段
	P3[0] = CP2(R - r, 0);
	P3[1] = CP2(R - r, -m * r);
	P3[2] = CP2(R - m * r, -r);
	P3[3] = CP2(R, -r);	
	for (int i = 0; i < 4; i++)//控制点转储为xOy面上的三维点
	{
		V0[i] = CP3(P0[i].x, P0[i].y, 0.0);
		V1[i] = CP3(P1[i].x, P1[i].y, 0.0);
		V2[i] = CP3(P2[i].x, P2[i].y, 0.0);
		V3[i] = CP3(P3[i].x, P3[i].y, 0.0);
	}
    revo0.ReadCubicBezierControlPoint(V0);	
	tran0.SetMatrix(revo0.GetVertexArrayName(), 48);
	tran0.RotateX(Alpha);
	revo1.ReadCubicBezierControlPoint(V1);	
	tran1.SetMatrix(revo1.GetVertexArrayName(), 48);
	tran1.RotateX(Alpha);
	revo2.ReadCubicBezierControlPoint(V2);	
	tran2.SetMatrix(revo2.GetVertexArrayName(), 48);
	tran2.RotateX(Alpha);
	revo3.ReadCubicBezierControlPoint(V3);	
	tran3.SetMatrix(revo3.GetVertexArrayName(), 48);
	tran3.RotateX(Alpha);
	InitializeLightingScene();
	revo0.patch.SetScene(pLight, pMaterial);//设置场景
	revo1.patch.SetScene(pLight, pMaterial);//设置场景
	revo2.patch.SetScene(pLight, pMaterial);//设置场景
	revo3.patch.SetScene(pLight, pMaterial);//设置场景
	texture.PrepareBitmap();//准备位图
	revo0.patch.SetTexture(&texture);
	revo1.patch.SetTexture(&texture);
	revo2.patch.SetTexture(&texture);
	revo3.patch.SetTexture(&texture);
}

CTestView::~CTestView()
{
	if (pLight != NULL)
	{
		delete pLight;
		pLight = NULL;
	}
	if (pMaterial != NULL)
	{
		delete pMaterial;
		pMaterial = NULL;
	}
	texture.DeleteObject();
}

void CTestView::InitializeLightingScene(void)//初始化光照场景
{
	//光照环境
	nLightSourceNumber = 1;//光源个数
	pLight = new CLighting(nLightSourceNumber);//一维光源动态数组
	pLight->LightSource[0].SetPosition(0, 0, 5000);//设置光源位置坐标	
	for (int i = 0; i < nLightSourceNumber; i++)
	{
		pLight->LightSource[i].L_Diffuse = CRGB(1.0, 1.0, 1.0);//光源的漫反射颜色	
		pLight->LightSource[i].L_Specular = CRGB(1.0, 1.0, 1.0);//光源镜面高光颜色
		pLight->LightSource[i].L_C0 = 1.0;//常数衰减系数
		pLight->LightSource[i].L_C1 = 0.0000001;//线性衰减系数	
		pLight->LightSource[i].L_C2 = 0.00000001;//二次衰减系数
		pLight->LightSource[i].L_OnOff = TRUE;//光源开启
	}
	//材质属性
	pMaterial = new CMaterial;
	pMaterial->SetAmbient(CRGB(0.847, 0.10, 0.075));//材质的环境反射率
	pMaterial->SetDiffuse(CRGB(0.852, 0.006, 0.026));//材质的漫反射率
	pMaterial->SetSpecular(CRGB(1.0, 1.0, 1.0));//材质的镜面反射率
	pMaterial->SetEmission(CRGB(0.0, 0.0, 0.0));//自身辐射的颜色
	pMaterial->SetExponent(50);//高光指数
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
	DoubleBuffer(pDC);
}

void CTestView::DoubleBuffer(CDC* pDC)//双缓冲
{
	CRect rect;//定义客户区矩形
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//设置视区范围,x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//客户区中心为原点
	CDC memDC;//内存DC
	memDC.CreateCompatibleDC(pDC);//创建一个与显示pDC兼容的内存memDC
	CBitmap NewBitmap, *pOldBitmap;//内存中承载的临时位图 
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//创建兼容位图 
	pOldBitmap = memDC.SelectObject(&NewBitmap);//将兼容位图选入memDC 
	//memDC.FillSolidRect(rect, pDC->GetBkColor());//按原来背景填充客户区，否则是黑色
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC自定义坐标系
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	DrawObject(&memDC);//向memDC绘制图形
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图
}

void CTestView::DrawObject(CDC* pDC)//绘制图形
{
	CZBuffer* pZBuffer = new CZBuffer;
	pZBuffer->InitialDepthBuffer(2000, 2000, 3000);//初始化深度缓冲器
	revo0.DrawRevolutionSurface(pDC, pZBuffer);
	revo1.DrawRevolutionSurface(pDC, pZBuffer);
	revo2.DrawRevolutionSurface(pDC, pZBuffer);
	revo3.DrawRevolutionSurface(pDC, pZBuffer);
	delete pZBuffer;
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


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_UP:
		Alpha = -5;
		tran0.RotateX(Alpha);
		tran1.RotateX(Alpha);
		tran2.RotateX(Alpha);
		tran3.RotateX(Alpha);
		break;
	case VK_DOWN:
		Alpha = +5;
		tran0.RotateX(Alpha);
		tran1.RotateX(Alpha);
		tran2.RotateX(Alpha);
		tran3.RotateX(Alpha);
		break;
	case VK_LEFT:
		Beta = -5;
		tran0.RotateY(Beta);
		tran1.RotateY(Beta);
		tran2.RotateY(Beta);
		tran3.RotateY(Beta);
		break;
	case VK_RIGHT:
		Beta = +5;
		tran0.RotateY(Beta);
		tran1.RotateY(Beta);
		tran2.RotateY(Beta);
		tran3.RotateY(Beta);
		break;
	default:
		break;
	}
	Invalidate(FALSE);
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
	Alpha = 5;
	tran0.RotateX(Alpha);
	tran1.RotateX(Alpha);
	tran2.RotateX(Alpha);
	tran3.RotateX(Alpha);
	
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}
