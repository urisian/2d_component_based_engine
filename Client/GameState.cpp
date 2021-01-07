#include "stdafx.h"
#include "GameState.h"


CGameState::CGameState()
{
}


CGameState::~CGameState()
{
}

bool CGameState::GetActivated(void)
{
	return m_activated;
}

void CGameState::SetActivated(bool activated)
{
	m_activated = activated;
}
