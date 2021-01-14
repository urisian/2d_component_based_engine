#include "stdafx.h"
#include "GameState.h"
#include "Mouse.h"
#include "DataStore.h"
#include "BaseTurret.h"
#include "Decoration.h"

CMouse* CGameState::m_s_pMouse = nullptr;

CGameState::CGameState()
{
}


CGameState::~CGameState()
{
}

void CGameState::Initialize(void)
{
	m_name = GetCurClassName(this);

	if(m_s_pMouse == nullptr)
		m_s_pMouse = new CMouse;

	int numOfDecoration;
	GET_VALUE(DATAID::STAGE, m_name, "numOfDecoration", numOfDecoration);
	for (int i = 0; i < numOfDecoration; ++i)
	{
		std::string objectKey;
		GET_VALUE(DATAID::STAGE, m_name, "decoration" + std::to_string(i) + "_objectKey", objectKey);
		CDecoration* pNewDecoration = new CDecoration(objectKey);

		GET_VALUE(DATAID::STAGE, m_name, "decoration" + std::to_string(i) + "_m_pos", pNewDecoration->GetPosition());
		
		if (i == 0)
			m_pBackground = pNewDecoration;
	}

	int numOfBaseTurret;
	GET_VALUE(DATAID::STAGE, m_name, "numOfBaseTurret", numOfBaseTurret);

	for (int i = 0; i < 1; ++i)
	{
		CBaseTurret* pNewTurret = new CBaseTurret;
		GET_VALUE(DATAID::STAGE, m_name, "baseTurret" + std::to_string(i) + "_m_pos", pNewTurret->GetPosition());
	}
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
