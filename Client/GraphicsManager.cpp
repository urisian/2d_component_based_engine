#include "stdafx.h"
#include "GraphicsManager.h"
#include "Application.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Camera.h"
#include "GraphicsComponent.h"
#include "Texture.h"


CGraphicsManager* CGraphicsManager::m_s_pInstance = nullptr;

CGraphicsManager * CGraphicsManager::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CGraphicsManager;

	return m_s_pInstance;
}

void CGraphicsManager::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CGraphicsManager::Initialize(void)
{
	m_screenHeight	= CApplication::GetInstance()->GetWndHeight();
	m_screenWidth	= CApplication::GetInstance()->GetWndWidth();

	InitDevice();
	InitVertexBuffer();
	InitIndexBuffer();
	InitStates();
	
	m_pCamera = new CCamera;
}

void CGraphicsManager::Update(void)
{
	m_pCamera->Update();

	m_pDevice->Clear(0, nullptr, 
					 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
					 D3DCOLOR_ARGB(255, 120, 120, 0), 
					 1.f, 0);

	m_pDevice->BeginScene();


	std::sort(m_vGraphicsComponents.begin(),
			  m_vGraphicsComponents.end(),
			  [](CGraphicsComponent* pGC1, CGraphicsComponent* pGC2)
				{
					return pGC1->GetZOrder() < pGC2->GetZOrder();
				});


	for (auto& element : m_vGraphicsComponents)
	{
		if (element->GetOwner()->GetActivated())
		{
			element->Update();

			SetWorldMatrix(element);
			m_pDevice->SetTexture(0, element->GetTexture());
			m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
			m_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, element->GetColor());
			m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		}
	}



	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

void CGraphicsManager::LateUpdate(void)
{
	for (auto& it = m_vGraphicsComponents.begin(); it != m_vGraphicsComponents.end();)
	{
		if ((*it)->GetOwner()->GetActivated())
			(*it)->LateUpdate();

		if ((*it)->GetNeedToBeDeleted())
		{
			SAFE_DELETE(*it);
			it = m_vGraphicsComponents.erase(it);
		}
		else
			++it;
	}
}

void CGraphicsManager::Release(void)
{
	SAFE_DELETE(m_pCamera);
}

void CGraphicsManager::AddGraphicsComponent(CGraphicsComponent * pGC)
{
	m_vGraphicsComponents.push_back(pGC);
}

void CGraphicsManager::InitDevice(void)
{
	D3DCAPS9 DeviceCap;
	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));

	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCap)))
	{
		MessageBox(nullptr, L"m_pD3D creation failed in InitDevice", L"CGraphicsManager.cpp", MB_OK);
		return;
	}

	DWORD vp = 0;
	if (DeviceCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	ZeroMemory(&m_d3dpParm, sizeof(m_d3dpParm));
	m_d3dpParm.BackBufferWidth				= m_screenWidth;
	m_d3dpParm.BackBufferHeight				= m_screenHeight;
	m_d3dpParm.BackBufferFormat				= D3DFMT_A8R8G8B8;
	m_d3dpParm.BackBufferCount				= 1;

	m_d3dpParm.MultiSampleType				= D3DMULTISAMPLE_NONE;
	m_d3dpParm.MultiSampleQuality			= 0;

	m_d3dpParm.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	m_d3dpParm.hDeviceWindow				= CApplication::GetInstance()->GetHandle();
	m_d3dpParm.Windowed						= !CApplication::GetInstance()->GetFullScreen();
	m_d3dpParm.EnableAutoDepthStencil		= TRUE;
	m_d3dpParm.AutoDepthStencilFormat		= D3DFMT_D24S8;

	m_d3dpParm.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	m_d3dpParm.PresentationInterval			= D3DPRESENT_INTERVAL_DEFAULT;

	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
								   CApplication::GetInstance()->GetHandle(), 
								   vp, 
								   &m_d3dpParm, &m_pDevice)))
	{
		MessageBox(nullptr, L"Device creation failed in InitDevice", L"CGraphicsManager.cpp", MB_OK);
		return;
	}
}

void CGraphicsManager::InitVertexBuffer(void)
{
	HRESULT result;
	//Create the vertex buffer
	result = m_pDevice->CreateVertexBuffer(4 * sizeof(CustomVertex),
										   0,
										   D3DFVF_CUSTOMVERTEX,
										   D3DPOOL_MANAGED,
										   &m_pVertexBuffer,
										   NULL);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"VertexBuffer creation failed in InitVertexBuffer", L"CGraphicsManager.cpp", MB_OK);
		return;
	}

	CustomVertex* vertices;

    m_pVertexBuffer->Lock( 0, 0, (void**)& vertices, 0 );

    //Set the position
    vertices[0].position = D3DXVECTOR3 (-0.5, -0.5, 0);
    vertices[1].position = D3DXVECTOR3 ( 0.5, -0.5, 0);
    vertices[2].position = D3DXVECTOR3 ( 0.5,  0.5, 0);
    vertices[3].position = D3DXVECTOR3 (-0.5,  0.5, 0);

    //Set the texture information
    vertices[0].texture  = D3DXVECTOR2 (0.0f, 1.0f);
    vertices[1].texture  = D3DXVECTOR2 (1.0f, 1.0f);
    vertices[2].texture  = D3DXVECTOR2 (1.0f, 0.0f);
    vertices[3].texture  = D3DXVECTOR2 (0.0f, 0.0f);

    m_pVertexBuffer->Unlock();
}

void CGraphicsManager::InitIndexBuffer(void)
{
	HRESULT result;

	result = m_pDevice->CreateIndexBuffer( 6 * sizeof(WORD),
										   0, 
										   D3DFMT_INDEX16,
										   D3DPOOL_MANAGED,
										   &m_pIndexBuffer, 
										   NULL);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"IndexBuffer creation failed in InitIndexBuffer", L"CGraphicsManager.cpp", MB_OK);
		return;
	}

	WORD* index = 0;

    m_pIndexBuffer->Lock( 0, 0, (void**)&index, 0 );

    //Match the vertex buffer and texture info
    index[0] = 0;
    index[1] = 1;
    index[2] = 2;
    index[3] = 0;
    index[4] = 2;
    index[5] = 3;

    m_pIndexBuffer->Unlock();
}

void CGraphicsManager::InitStates(void)
{
	m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof( CustomVertex ) );
    m_pDevice->SetIndices(m_pIndexBuffer);
    m_pDevice->SetFVF( D3DFVF_CUSTOMVERTEX ); 

    //This is for culling
    m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    //This is for light. Turn off the 3D light.
    m_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
    //Turn on the z-buffer
    m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    m_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );

    //You NEED these to do alpha blending!!!!
    m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );//Transparent

    m_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

    //Under code is really needed!! for the alpha blending
    m_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
    m_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    m_pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);

    //Set texture state
    m_pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
    m_pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_CONSTANT);

	//Get the alpha from the texture
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CONSTANT);

	
}

void CGraphicsManager::SetWorldMatrix(CGraphicsComponent* pGC)
{
	D3DXMATRIX rotateX, rotateY, rotateZ, scale, trans, result;
	D3DXMatrixIdentity(&rotateX); D3DXMatrixIdentity(&rotateY); D3DXMatrixIdentity(&rotateZ);
	D3DXMatrixIdentity(&scale); D3DXMatrixIdentity(&trans);D3DXMatrixIdentity(&result);

	D3DXMatrixRotationZ(&rotateZ, pGC->GetRotation().z);
	D3DXMatrixRotationY(&rotateY, pGC->GetRotation().y);
	D3DXMatrixRotationX(&rotateX, pGC->GetRotation().x);

	D3DXMatrixScaling(&scale, pGC->GetSize().x, pGC->GetSize().y, pGC->GetSize().z);
	D3DXMatrixTranslation(&trans, pGC->GetPosition().x, pGC->GetPosition().y, pGC->GetPosition().z);

	result = scale * rotateX * rotateY * rotateZ * trans;

	m_pDevice->SetTransform(D3DTS_WORLD, &result);
}

CGraphicsManager::CGraphicsManager()
{
}


CGraphicsManager::~CGraphicsManager()
{
	Release();
}
