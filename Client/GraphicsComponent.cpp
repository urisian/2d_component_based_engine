#include "stdafx.h"
#include "GraphicsComponent.h"
#include "Texture.h"
#include "DataStore.h"
#include "TextureStore.h"
#include "PhysicsComponent.h"
#include "GraphicsManager.h"

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

	m_pCTexture		= nullptr;
}


CGraphicsComponent::~CGraphicsComponent()
{
	Release();
}

void CGraphicsComponent::Initialize(void)
{
	__super::Initialize();
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), "m_zOrder", m_zOrder);
	m_pCTexture = GET_TEXTURE(m_pOwner->GetObjID(), m_pOwner->GetObjectKey());

	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), m_pOwner->GetStateKey() + "_m_aniSecPerFrame", m_aniSecPerFrame);
	m_curAniIndex = 0;
	m_maxAniIndex = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey()).size();

	CGraphicsManager::GetInstance()->AddGraphicsComponent(this);
}

void CGraphicsComponent::Update(void)
{
	__super::Update();

	m_position	= m_pOwner->GetPosition() + m_pOwner->GetParentPosition();

	m_rotation	= m_pOwner->GetRotation();
	m_size		= m_pOwner->GetSize();

	m_pTexture = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey())[(int)m_curAniIndex]->pTexture;

	PlayAnimation();
}

void CGraphicsComponent::LateUpdate(void)
{
}

void CGraphicsComponent::Release(void)
{
}

void CGraphicsComponent::PlayAnimation(void)
{
	m_curAniIndex += m_aniSecPerFrame;
	if (m_curAniIndex > (float)m_maxAniIndex)
		m_curAniIndex -= (float)m_maxAniIndex;
}

void CGraphicsComponent::StateChangeInit(void)
{
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), m_pOwner->GetStateKey() + "_m_aniSecPerFrame", m_aniSecPerFrame);
	m_curAniIndex = 0;
	m_maxAniIndex = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey()).size();
}
