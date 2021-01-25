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
	m_zOrder			= 0;

	m_position			= {};
	m_rotation			= {};
	m_size				= {};

	//ARGB
	m_color			= 0xffffffff;
	m_xFlip			= false;

	m_pAnimation	= nullptr;
	m_pCTexture		= nullptr;
	m_isOrtho		= false;
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
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), "m_isOrtho", m_isOrtho);
	//텍스쳐 세팅
	m_pCTexture = GET_TEXTURE(m_pOwner->GetObjID(), m_pOwner->GetObjectKey());

	//애니메이션 세팅
	if(m_pCTexture->GetTexInfos(m_pOwner->GetStateKey()).size() > 1)
		m_pAnimation = new CAnimation(this);

	m_pTexture = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey())[0]->pTexture;
	CGraphicsManager::GetInstance()->AddGraphicsComponent(this);
}

void CGraphicsComponent::Update(void)
{
	__super::Update();
}

void CGraphicsComponent::LateUpdate(void)
{
	__super::LateUpdate();
	m_position = m_pOwner->GetPosition() + m_pOwner->GetParentPosition();

	m_rotation = m_pOwner->GetRotation();
	m_size = m_pOwner->GetSize();

	if (m_xFlip && m_size.x > 0)
		m_size.x *= -1;
	else if (!m_xFlip && m_size.x < 0)
		m_size.x *= -1;

	if (m_pAnimation != nullptr)
	{
		m_pAnimation->LateUpdate();
		m_pTexture = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey())[(int)m_pAnimation->GetCurIndex()]->pTexture;
	}
	else
		m_pTexture = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey())[0]->pTexture;
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

	m_pAnimation->StateChangeInit();
}
