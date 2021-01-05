
// MFCToolView.cpp : CMFCToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCToolView ����/�Ҹ�

CMFCToolView::CMFCToolView()
//	:m_pSingle_Texture(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFCToolView �׸���

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
	// ���� ��ġ�� �̿��ؼ� �׸��� �׷�����. �׷��� ���ؼ� �ϴ� ��ġ�� �����ϱ� ���� Ŭ������ �����Ұ�. 
// 	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
// 	pDC->Rectangle(100, 100, 200, 200);
// 	pDC->Ellipse(100, 100, 200, 200);
	//�׸��� �׷����� ���� 
	//
	//1.�ĸ���۸� ����� 
	//2. �ĸ���ۿ� �׸��� �׸���. 
	//3. ������ۿ� ��ü �� �ÿ�. 
	CGraphic_Device::Get_Instance()->Render_Begin(); 
	// ��������Ʈ �İ�ü�� �̿��Ͽ� �׸� �׸�. 
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


// CMFCToolView �μ�

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCToolView ����

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView �޽��� ó����


void CMFCToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
