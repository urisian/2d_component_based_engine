#include "stdafx.h"
#include "MouseIdleState.h"
#include "Object.h"
#include "GraphicsComponent.h"
#include "InputManager.h"
#include "StateMachine.h"

CMouseIdleState::CMouseIdleState(CObject* pOwner) : CObjectState(pOwner)
{
}


CMouseIdleState::~CMouseIdleState()
{
}

void CMouseIdleState::OnStart(void)
{
	m_pOwner->GetComponent<CGraphicsComponent>()->StateChangeInit();
}

void CMouseIdleState::OnUpdate(void)
{
	if (CInputManager::GetInstance()->KeyPress(MOUSE_LEFT))
	{
		m_pOwner->SetStateKey("Clicked");
		m_pOwner->GetStateMachine()->SetNextState(m_pOwner->GetState(m_pOwner->GetStateKey()));
	}
}

void CMouseIdleState::OnExit(void)
{
}
