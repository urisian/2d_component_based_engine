#include "stdafx.h"
#include "Background.h"
#include "GraphicsComponent.h"
#include "ObjectManager.h"
#include "DataStore.h"

CBackground::CBackground(std::string objectKey) : CObject()
{
	m_objectKey = objectKey;
	
	Initialize();
}


CBackground::~CBackground()
{
}

void CBackground::Initialize(void)
{
	m_objID = OBJID::BACKGROUND;
	m_dataID = DATAID::BACKGROUND;

	GET_VALUE(m_dataID, m_objectKey, "m_stateKey", m_stateKey);

	CGraphicsComponent* pComponent = AddComponent<CGraphicsComponent>();
	pComponent->Initialize();

	CObjectManager::GetInstance()->AddObject(this, m_objID);
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
