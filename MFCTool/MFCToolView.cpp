
// MFCToolView.cpp : CMFCToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCTool.h"
#endif

#include "MFCToolDoc.h"
#include "MFCToolView.h"
#include "Graphic_Device.h"
#include "Single_Texture.h"
#include "Texture_Manager.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView
HWND g_hWND; 
IMPLEMENT_DYNCREATE(CMFCToolView, CView)

BEGIN_MESSAGE_MAP(CMFCToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCToolView 생성/소멸

CMFCToolView::CMFCToolView()
//	:m_pSingle_Texture(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_iSpeed = 2; 
}

CMFCToolView::~CMFCToolView()
{
// 	if (m_pSingle_Texture)
// 	{
// 		delete m_pSingle_Texture; 
// 		m_pSingle_Texture = nullptr; 
// 	}
	CGraphic_Device::Destroy_Instance(); 
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCToolView 그리기

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_iR += m_iSpeed; 
	m_fAngle += 3.f; 
	if (m_iR > 255 || 0>= m_iR)
	{
		m_iSpeed *= -1;
	}
	// 이제 장치를 이용해서 그림을 그려보자. 그러기 위해선 일단 장치를 제어하기 위한 클래스를 생성할것. 
// 	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
// 	pDC->Rectangle(100, 100, 200, 200);
// 	pDC->Ellipse(100, 100, 200, 200);
	//그림이 그려지는 과정 
	//
	//1.후면버퍼를 지운다 
	//2. 후면버퍼에 그림을 그린다. 
	//3. 전면버퍼와 교체 후 시연. 
	CGraphic_Device::Get_Instance()->Render_Begin(); 
	// 스프라이트 컴객체를 이용하여 그림 그림. 
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", 37); 
	if (nullptr == pTexInfo)
	{
		return; 
	}
	UINT iCenterX = pTexInfo->tImageInfo.Width >> 1; 
	UINT iCenterY = pTexInfo->tImageInfo.Height >> 1;
	D3DXMATRIX matScale, matRotZ, matTrans, matWorld ;
	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.f); 
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);
	matWorld = matScale * matRotZ * matTrans;
	/*RECT rc = { 0, 0, 100, 100 }; */
	CGraphic_Device::Get_Instance()->Get_SPrite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_SPrite()->Draw(pTexInfo->pTexture, nullptr/*&rc*/, &D3DXVECTOR3(float(iCenterX), float(iCenterY), 0.f), nullptr/*&D3DXVECTOR3(400.f, 300.f, 0.f)*/, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGraphic_Device::Get_Instance()->Render_End();
}


// CMFCToolView 인쇄

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCToolView 진단

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView 메시지 처리기


void CMFCToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	g_hWND = m_hWnd; 
	if (FAILED(CGraphic_Device::Get_Instance()->Ready_Graphic_Device()))
	{
		ERR_MSG(L"Ready_GraphicDevice Failed"); 
		return; 
	}
// 	if (!m_pSingle_Texture)
// 	{
// 		m_pSingle_Texture = new CSingle_Texture; 
// 		m_pSingle_Texture->Insert_Texture(L"../Texture/Cube.png", L"Cube");;
// 	}
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::MULTI_TEX,L"../Texture/Stage/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 38 )))
	{
		ERR_MSG(L"Insert_Texture_Manager Failed");
		return;
	}
}
