#include "stdafx.h"
#include "ArcherTurret.h"
#include "StateMachine.h"
#include "ArcherUnit.h"
#include "ArrowProjectile.h"
#include "FRC.h"

CArcherTurret::CArcherTurret()
{
	m_pArchers[0] = nullptr;
	m_pArchers[1] = nullptr;

	m_shootTurn = 0;
	m_attackTimer = 0;
	Initialize();
}


CArcherTurret::~CArcherTurret()
{
	Release();
}

void CArcherTurret::Initialize(void)
{
	__super::Initialize();
	m_attackTimer = m_attackCooltime;
}

void CArcherTurret::Update(void)
{
	__super::Update();


	m_pArchers[0]->SetTarget(m_pTarget);
	m_pArchers[1]->SetTarget(m_pTarget);

	if (m_pTarget != nullptr)
	{
		if (m_attackTimer >= m_attackCooltime)
		{
			m_pArchers[m_shootTurn % 2]->SetAttackNow(true);
			m_attackTimer = 0.f;
		}
	}

	m_attackTimer += GET_DT();
}

void CArcherTurret::LateUpdate(void)
{
	__super::LateUpdate();
}

void CArcherTurret::Release(void)
{
	m_pArchers[0]->SetNeedToBeDeleted(true);
	m_pArchers[1]->SetNeedToBeDeleted(true);
}

void CArcherTurret::UpgradeTurret(int increase)
{
	__super::UpgradeTurret(increase);
	m_pArchers[0]->UpgradeUnit(increase);
	m_pArchers[1]->UpgradeUnit(increase);
}

void CArcherTurret::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();

	for (int i = 0; i < 2; ++i)
	{
		m_pArchers[i] = new CArcherUnit(this);
		if(i == 1)
			m_pArchers[i]->GetPosition().x *= (-1);
		m_pArchers[i]->AddChildAndComponents();
	}
}

void CArcherTurret::InitializeComponents(void)
{
}

