#include "stdafx.h"
#include "GraphicsComponent.h"
#include "Texture.h"
#include "DataStore.h"
#include "TextureStore.h"
#include "PhysicsComponent.h"
#include "GraphicsManager.h"
#include "Animation.h"

CGraphicsComponent::CGraphicsComponent(CObject* pOwner) : CComponent(pOwner)
{
	m_aniSecPerFrame	= 0;
	m_curAniIndex		= 0;
	m_maxAniIndex		= 0;

	m_zOrder			= 0;

	m_position			= {};
	m_rotation			= {};
	m_size				= {};

	//ARGB
	m_color			= 0xffffffff;

	m_pAnimation	= nullptr;
	m_pCTexture		= nullptr;
}


CGraphicsComponent::~CGraphicsComponent()
{
	Release();
}

void CGraphicsComponent::Initialize(void)
{
	__super::Initialize();
	//ZOrder세팅
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), "m_zOrder", m_zOrder);
	//텍스쳐 세팅
	m_pCTexture = GET_TEXTURE(m_pOwner->GetObjID(), m_pOwner->GetObjectKey());

	//애니메이션 세팅
	if(m_pCTexture->GetTexInfos(m_pOwner->GetStateKey()).size() > 1)
		m_pAnimation = new CAnimation(this);

	CGraphicsManager::GetInstance()->AddGraphicsComponent(this);
}

void CGraphicsComponent::Update(void)
{
	__super::Update();

	m_position	= m_pOwner->GetPosition() + m_pOwner->GetParentPosition();

	m_rotation	= m_pOwner->GetRotation();
	m_size		= m_pOwner->GetSize();

	

	if (m_pAnimation != nullptr)
	{
		m_pAnimation->Update();
		m_pTexture = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey())[(int)m_pAnimation->GetCurIndex()]->pTexture;
	}
	else
		m_pTexture = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey())[0]->pTexture;
}

void CGraphicsComponent::LateUpdate(void)
{
}

void CGraphicsComponent::Release(void)
{
	SAFE_DELETE(m_pAnimation);
}


void CGraphicsComponent::StateChangeInit(void)
{
	if (m_pAnimation == nullptr && (m_pCTexture->GetTexInfos(m_pOwner->GetStateKey()).size() > 1))
		m_pAnimation = new CAnimation(this);
	else if (m_pAnimation == nullptr)
		return;

	m_pAnimation->Initialize();
}
