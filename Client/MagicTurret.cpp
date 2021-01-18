#include "stdafx.h"
#include "MagicTurret.h"
#include "MagicianUnit.h"
#include "FRC.h"

CMagicTurret::CMagicTurret()
{
	m_pMagician = nullptr;
	Initialize();
}


CMagicTurret::~CMagicTurret()
{
}

void CMagicTurret::Initialize(void)
{
	__super::Initialize();
}

void CMagicTurret::Update(void)
{
	__super::Update();
	
	m_pMagician->SetTarget(m_pTarget);
	m_pMagician->GetAttackTimer() += GET_DT();
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
	m_pMagician->UpgradeUnit(increase);
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

