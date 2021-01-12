#include "stdafx.h"
#include "UserInterface.h"
#include "DataStore.h"
#include "ObjectManager.h"
#include "GraphicsComponent.h"

CUserInterface::CUserInterface(void)
{
}


CUserInterface::~CUserInterface()
{
}

void CUserInterface::Initialize(void)
{
	m_objID = OBJID::UI;
	m_dataID = DATAID::UI;

	__super::Initialize();


	AddComponent<CGraphicsComponent>();
}

void CUserInterface::Update(void)
{
	__super::Update();
	//GetComponent<CGraphicsComponent>()->Update();
}

void CUserInterface::LateUpdate(void)
{
}

void CUserInterface::Release(void)
{
}
