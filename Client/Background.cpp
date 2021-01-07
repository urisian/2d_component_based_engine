#include "stdafx.h"
#include "Background.h"
#include "GraphicsComponent.h"

CBackground::CBackground(std::string objectKey, std::string stateKey/* = "Idle"*/) : CObject()
{
	m_objectKey = objectKey;
	m_stateKey	= stateKey;

	CGraphicsComponent* pComponent = AddComponent<CGraphicsComponent>();
	pComponent->Initialize();
}


CBackground::~CBackground()
{
}

void CBackground::Update(void)
{
}

void CBackground::LateUpdate(void)
{
}

void CBackground::Release(void)
{
}
