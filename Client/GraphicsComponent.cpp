#include "stdafx.h"
#include "GraphicsComponent.h"
#include "Texture.h"
#include "DataStore.h"
#include "TextureStore.h"
#include "PhysicsComponent.h"

CGraphicsComponent::CGraphicsComponent()
{
	m_curAniIndex	= 0;
	m_maxAniIndex	= 0;

	m_zOrder		= 0;

	m_position		= {};
	m_rotation		= {};
	m_size			= {};

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
	m_position	= m_pOwner->GetPosition();
	if (m_pOwner->GetParent() != nullptr)
		m_position += m_pOwner->GetParentPosition();

	m_rotation	= m_pOwner->GetRotation();
	m_size		= m_pOwner->GetSize();

	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), m_pOwner->GetStateKey() + "_m_zOrder", m_zOrder);

	m_pCTexture		= GET_TEXTURE(m_pOwner->GetObjID(), m_pOwner->GetObjectKey());
	m_pTexture		= m_pCTexture->GetTexInfos(m_pOwner->GetStateKey())[m_curAniIndex]->pTexture;
	m_maxAniIndex	= m_pCTexture->GetTexInfos(m_pOwner->GetStateKey()).size();
}

void CGraphicsComponent::Update(void)
{
	m_position	= m_pOwner->GetPosition();
	if (m_pOwner->GetParent() != nullptr)
		m_position += m_pOwner->GetParentPosition();

	m_rotation	= m_pOwner->GetRotation();
	m_size		= m_pOwner->GetSize();

	m_pTexture = m_pCTexture->GetTexInfos(m_pOwner->GetStateKey())[m_curAniIndex]->pTexture;

}

void CGraphicsComponent::LateUpdate(void)
{
}

void CGraphicsComponent::Release(void)
{
}
