#include "stdafx.h"
#include "Decoration.h"
#include "GraphicsComponent.h"
#include "StateMachine.h"

CDecoration::CDecoration(std::string objectKey, std::string stateKey, CObject* pParent)
{
	m_pParent = pParent;
	m_objectKey = objectKey;
	m_stateKey = stateKey;
	Initialize();
}


CDecoration::~CDecoration()
{
	Release();
}

void CDecoration::Initialize(void)
{
	m_objID = OBJID::DECORATION;
	m_dataID = DATAID::DECORATION;

	__super::Initialize();
}

void CDecoration::Update(void)
{
	__super::Update();
}

void CDecoration::LateUpdate(void)
{
	__super::LateUpdate();
}

void CDecoration::Release(void)
{
}

void CDecoration::AddChildAndComponents(void)
{
	AddComponent<CGraphicsComponent>();
}

void CDecoration::InitializeComponents(void)
{
}
