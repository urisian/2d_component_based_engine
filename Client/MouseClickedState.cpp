#include "stdafx.h"
#include "MouseClickedState.h"
#include "GraphicsComponent.h"
#include "InputManager.h"
#include "StateMachine.h"

CMouseClickedState::CMouseClickedState(CObject* pOwner) : CObjectState(pOwner)
{
}


CMouseClickedState::~CMouseClickedState()
{
}

void CMouseClickedState::OnStart(void)
{
	m_pOwner->GetComponent<CGraphicsComponent>()->StateChangeInit();
}

void CMouseClickedState::OnUpdate(void)
{
	if (!CInputManager::GetInstance()->KeyPress(MOUSE_LEFT))
	{
		m_pOwner->SetStateKey("Idle");
		m_pOwner->GetStateMachine()->SetNextState(m_pOwner->GetState(m_pOwner->GetStateKey()));
	}
}

void CMouseClickedState::OnExit(void)
{
}
