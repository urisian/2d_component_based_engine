#include "stdafx.h"
#include "DecorationIdleState.h"
#include "GraphicsComponent.h"

CDecorationIdleState::CDecorationIdleState(CObject* pOwner) : CObjectState(pOwner)
{
}


CDecorationIdleState::~CDecorationIdleState()
{
}

void CDecorationIdleState::OnStart(void)
{
	m_pOwner->GetComponent<CGraphicsComponent>()->StateChangeInit();
}

void CDecorationIdleState::OnUpdate(void)
{
	
}

void CDecorationIdleState::OnExit(void)
{
}
