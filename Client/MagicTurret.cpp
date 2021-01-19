#include "stdafx.h"
#include "MagicTurret.h"
#include "MagicianUnit.h"
#include "FRC.h"
#include "DataStore.h"

CMagicTurret::CMagicTurret()
{
	m_pMagician = nullptr;
	Initialize();
}


CMagicTurret::~CMagicTurret()
{
	Release();
}

void CMagicTurret::Initialize(void)
{
	__super::Initialize();
	m_attackTimer = m_attackCooltime;
}

void CMagicTurret::Update(void)
{
	__super::Update();
	
	m_pMagician->SetTarget(m_pTarget);
	if (m_pTarget != nullptr)
	{
		if (m_attackTimer >= m_attackCooltime)
		{
			m_pMagician->SetAttackNow(true);
			m_attackTimer = 0.f;
		}
	}
	
	m_attackTimer += GET_DT();
}

void CMagicTurret::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMagicTurret::Release(void)
{
	m_pMagician->SetNeedToBeDeleted(true);
}

void CMagicTurret::UpgradeTurret(int increase)
{
	__super::UpgradeTurret(increase);
}

void CMagicTurret::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	m_pMagician = new CMagicianUnit(this);
	m_pMagician->AddChildAndComponents();
}

void CMagicTurret::InitializeComponents(void)
{
}

