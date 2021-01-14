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
	//ZOrder����
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), "m_zOrder", m_zOrder);
	//�ؽ��� ����
	m_pCTexture = GET_TEXTURE(m_pOwner->GetObjID(), m_pOwner->GetObjectKey());

	//�ִϸ��̼� ����
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

	m_pTexture = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey())[(int)m_pAnimation->GetCurIndex()]->pTexture;

	m_pAnimation->Update();
}

void CGraphicsComponent::LateUpdate(void)
{
}

void CGraphicsComponent::Release(void)
{
}


void CGraphicsComponent::StateChangeInit(void)
{
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), m_pOwner->GetStateKey() + "_m_aniSecPerFrame", m_aniSecPerFrame);
	m_curAniIndex = 0;
	m_maxAniIndex = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey()).size();
}
