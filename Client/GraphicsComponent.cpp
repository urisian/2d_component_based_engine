#include "stdafx.h"
#include "GraphicsComponent.h"
#include "Texture.h"
#include "DataStore.h"
#include "TextureStore.h"

CGraphicsComponent::CGraphicsComponent()
{
	m_curAniIndex	= 0;
	m_maxAniIndex	= 0;

	m_position		= {};
	m_rotation		= {};
	m_size			= {};

	//ARGB
	m_color			= 0xffffffff;

	m_pCTexture		= nullptr;
}


CGraphicsComponent::~CGraphicsComponent()
{
}

void CGraphicsComponent::Initialize(void)
{
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), "m_position", m_position);
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), "m_rotation", m_rotation);
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), "m_size", m_size);

	m_pCTexture		= GET_TEXTURE(m_pOwner->GetObjID(), m_pOwner->GetObjectKey());
	m_pTexture		= m_pCTexture->GetTexInfos(m_pOwner->GetStateKey())[m_curAniIndex]->pTexture;
	m_maxAniIndex	= m_pCTexture->GetTexInfos(m_pOwner->GetStateKey()).size();
}

void CGraphicsComponent::Update(void)
{
}

int & CGraphicsComponent::GetCurAniIndex(void)
{
	return m_curAniIndex;
}

int & CGraphicsComponent::GetMaxAniIndex(void)
{
	return m_maxAniIndex;
}

D3DXVECTOR3 & CGraphicsComponent::GetPosition(void)
{
	return m_position;
}

D3DXVECTOR3 & CGraphicsComponent::GetRotation(void)
{
	return m_rotation;
}

D3DXVECTOR3 & CGraphicsComponent::GetSize(void)
{
	return m_size;
}

D3DCOLOR & CGraphicsComponent::GetColor(void)
{
	return m_color;
}

CTexture * CGraphicsComponent::GetCTexture(void)
{
	return m_pCTexture;
}

LPDIRECT3DTEXTURE9 CGraphicsComponent::GetTexture(void)
{
	return m_pTexture;
}
