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
	Release();
}

void CUserInterface::Initialize(void)
{
	m_objID = OBJID::UI;
	m_dataID = DATAID::UI;

	__super::Initialize();

}

void CUserInterface::Update(void)
{
	__super::Update();
	 
}

void CUserInterface::LateUpdate(void)
{
	__super::LateUpdate();
}

void CUserInterface::Release(void)
{
}

void CUserInterface::AddChildAndComponents(void)
{
	AddComponent<CGraphicsComponent>();
}

