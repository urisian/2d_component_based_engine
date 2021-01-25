#include "stdafx.h"
#include "FireRain.h"
#include "ClickableComponent.h"
#include "FRC.h"
#include "InputManager.h"
#include "DataStore.h"
#include "FireRainProjectile.h"
CFireRain::CFireRain()
{
	Initialize();
}


CFireRain::~CFireRain()
{
}

void CFireRain::Initialize(void)
{
	__super::Initialize();
	m_timer = 0;

	GET_VALUE(m_dataID, m_objectKey, "m_cooltime", m_cooltime);
}

void CFireRain::Update(void)
{
	__super::Update();
	m_timer += GET_DT();
}

void CFireRain::LateUpdate(void)
{
	__super::LateUpdate();

	if (IMKEY_UP(MOUSE_LEFT) && m_stateKey == "Clicked" && !GetComponent<CClickableComponent>()->GetMouseOver())
	{
		for (int i = 0; i < 10; ++i)
		{
			CFireRainProjectile* pFireRainProjectile = new CFireRainProjectile;
			pFireRainProjectile->AddChildAndComponents();
		}

		m_stateKey = "Idle";
	}
}

void CFireRain::Release(void)
{
}

void CFireRain::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	AddComponent<CClickableComponent>()->SetPlayFunc(std::bind(&CFireRain::Selected, this));
}

void CFireRain::InitializeComponents(void)
{
}

void CFireRain::Selected(void)
{
	if (m_stateKey == "Idle")
		m_stateKey = "Clicked";
	else if (m_stateKey == "Clicked")
		m_stateKey = "Idle";
}
