#include "stdafx.h"
#include "UserInterface.h"
#include "DataStore.h"
#include "ObjectManager.h"
#include "GraphicsComponent.h"

CUserInterface::CUserInterface(std::string objectKey)
{
	m_objectKey = objectKey;

	Initialize();
}


CUserInterface::~CUserInterface()
{
}

void CUserInterface::Initialize(void)
{
	m_objID = OBJID::UI;
	m_dataID = DATAID::UI;

	GET_VALUE(m_dataID, m_objectKey, "m_stateKey", m_stateKey);

	CGraphicsComponent* pComponent = AddComponent<CGraphicsComponent>();
	pComponent->Initialize();

	CObjectManager::GetInstance()->AddObject(this, m_objID);
}

void CUserInterface::Update(void)
{
}

void CUserInterface::LateUpdate(void)
{
}

void CUserInterface::Release(void)
{
}
