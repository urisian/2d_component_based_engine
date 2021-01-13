#include "stdafx.h"
#include "Mouse.h"
#include "InputManager.h"
#include "StateMachine.h"
#include "MouseIdleState.h"
#include "MouseClickedState.h"

CMouse::CMouse()
{
	Initialize();
}


CMouse::~CMouse()
{
}

void CMouse::Initialize(void)
{
	__super::Initialize();
	
	InitializeStates();
	m_pStateMachine->SetNextState(GetState(m_stateKey));
}

void CMouse::Update(void)
{
	__super::Update();

	m_position = GET_MOUSE_POS();
	m_position.x += m_size.x / 2.f;
	m_position.y -= m_size.y / 2.f;
}

void CMouse::LateUpdate(void)
{
}

void CMouse::Release(void)
{
}

void CMouse::InitializeStates(void)
{
	AddState("Idle",	new CMouseIdleState		(this));
	AddState("Clicked", new CMouseClickedState	(this));
}
