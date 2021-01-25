#include "stdafx.h"
#include "Reinforce.h"
#include "ClickableComponent.h"
#include "FRC.h"
#include "InputManager.h"
#include "DataStore.h"
#include "ReinforceUnit.h"
CReinforce::CReinforce()
{
	Initialize();
}


CReinforce::~CReinforce()
{
}

void CReinforce::Initialize(void)
{
	__super::Initialize();
	m_timer = 0;

	GET_VALUE(m_dataID, m_objectKey, "m_cooltime", m_cooltime);
}

void CReinforce::Update(void)
{
	__super::Update();
	m_timer += GET_DT();
}

void CReinforce::LateUpdate(void)
{
	__super::LateUpdate();

	if (IMKEY_UP(MOUSE_LEFT) && m_stateKey == "Clicked" && !GetComponent<CClickableComponent>()->GetMouseOver())
	{
		for (int i = 0; i < 2; ++i)
		{
			CReinforceUnit* pRU = new CReinforceUnit(i);
			pRU->AddChildAndComponents();
			m_stateKey = "Idle";
		}
	}
}

void CReinforce::Release(void)
{
}

void CReinforce::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	AddComponent<CClickableComponent>()->SetPlayFunc(std::bind(&CReinforce::Selected, this));
}

void CReinforce::InitializeComponents(void)
{
}

void CReinforce::Selected(void)
{
	if (m_stateKey == "Idle")
		m_stateKey = "Clicked";
	else if (m_stateKey == "Clicked")
		m_stateKey = "Idle";
}
