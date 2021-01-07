#include "stdafx.h"
#include "GraphicsComponent.h"
#include "Texture.h"

CGraphicsComponent::CGraphicsComponent()
{
	m_position	= {};
	m_rotation	= {};
	m_scale		= {};
	m_pCTexture = new CTexture;
}


CGraphicsComponent::~CGraphicsComponent()
{
}

D3DXVECTOR3 & CGraphicsComponent::GetPosition(void)
{
	return m_position;
}

D3DXVECTOR3 & CGraphicsComponent::GetRotation(void)
{
	return m_rotation;
}

D3DXVECTOR3 & CGraphicsComponent::GetScale(void)
{
	return m_scale;
}

CTexture * CGraphicsComponent::GetCTexture(void)
{
	return m_pCTexture;
}
