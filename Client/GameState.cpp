#include "stdafx.h"
#include "GameState.h"
#include "Mouse.h"

CMouse* CGameState::m_s_pMouse = nullptr;

CGameState::CGameState()
{
}


CGameState::~CGameState()
{
}

void CGameState::Initialize(void)
{
	if(m_s_pMouse == nullptr)
		m_s_pMouse = new CMouse;
}

void CGameState::Release(void)
{
	for (auto& stateObject : m_vStateObjects)
		stateObject->SetNeedToBeDeleted(true);
}

bool CGameState::GetActivated(void)
{
	return m_activated;
}

void CGameState::SetActivated(bool activated)
{
	m_activated = activated;
}

std::vector<CObject*>& CGameState::GetStateObjects(void)
{
	return m_vStateObjects;
}
