#include "stdafx.h"
#include "Decoration.h"
#include "GraphicsComponent.h"
#include "StateMachine.h"

CDecoration::CDecoration(std::string objectKey, std::string stateKey)
{
	m_objectKey = objectKey;
	m_stateKey = stateKey;
	Initialize();
}


CDecoration::~CDecoration()
{
}

void CDecoration::Initialize(void)
{
	m_objID = OBJID::DECORATION;
	m_dataID = DATAID::DECORATION;

	__super::Initialize();

	AddComponent<CGraphicsComponent>();

}

void CDecoration::Update(void)
{
	__super::Update();
}

void CDecoration::LateUpdate(void)
{
}

void CDecoration::Release(void)
{
}
