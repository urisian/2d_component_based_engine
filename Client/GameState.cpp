#include "stdafx.h"
#include "GameState.h"
#include "Mouse.h"
#include "DataStore.h"
#include "BaseTurret.h"
#include "Decoration.h"
#include "GraphicsComponent.h"

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

	MakeMouse();
	SetupDecorations();	
}

void CGameState::LateUpdate(void)
{
}

void CGameState::Release(void)
{
}

void CGameState::MakeMouse(void)
{
	if (m_s_pMouse == nullptr)
	{
		m_s_pMouse = new CMouse;
		m_s_pMouse->AddChildAndComponents();
	}
}

void CGameState::SetupDecorations(void)
{
	int numOfDecoration;
	GET_VALUE(DATAID::STAGE, m_name, "numOfDecoration", numOfDecoration);
	for (int i = 0; i < numOfDecoration; ++i)
	{
		std::string objectKey;
		GET_VALUE(DATAID::STAGE, m_name, "decoration" + std::to_string(i) + "_objectKey", objectKey);
		CDecoration* pNewDecoration = new CDecoration(objectKey);
		GET_VALUE(DATAID::STAGE, m_name, "decoration" + std::to_string(i) + "_m_pos", pNewDecoration->GetPosition());
		pNewDecoration->AddChildAndComponents();

		if (i == 0)
			m_pBackground = pNewDecoration;
	}
}

