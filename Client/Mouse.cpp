#include "stdafx.h"
#include "Mouse.h"
#include "InputManager.h"

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

	m_position = GET_MOUSE_POS();
}

void CMouse::Update(void)
{
	__super::Update();

	m_position = GET_MOUSE_POS();
	m_position.x += m_size.x / 2.f;
	m_position.y -= m_size.y / 2.f;

	if (CInputManager::GetInstance()->KeyPress(MOUSE_LEFT))
	{
		m_stateKey = "Clicked";
	}
	else
	{
		m_stateKey = "Idle";
	}
}

void CMouse::LateUpdate(void)
{
}

void CMouse::Release(void)
{
}
