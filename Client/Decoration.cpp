#include "stdafx.h"
#include "Decoration.h"
#include "GraphicsComponent.h"
#include "StateMachine.h"
#include "DecorationIdleState.h"

CDecoration::CDecoration(std::string objectKey)
{
	m_objectKey = objectKey;
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

	InitializeStates();

	m_pStateMachine->SetNextState(GetState(m_stateKey));
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

void CDecoration::InitializeStates(void)
{
	AddState("Idle", new CDecorationIdleState(this));
}
