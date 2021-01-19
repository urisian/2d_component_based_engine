#include "stdafx.h"
#include "BarrackTurret.h"
#include "FRC.h"
#include "SoldierUnit.h"
#include "GraphicsComponent.h"
#include "Animation.h"

CBarrackTurret::CBarrackTurret()
{
	for (int i = 0; i < 3; ++i)
		m_pSoldiers[i] = nullptr;

	Initialize();
}


CBarrackTurret::~CBarrackTurret()
{
	Release();
}

void CBarrackTurret::Initialize(void)
{
	__super::Initialize();
}

void CBarrackTurret::Update(void)
{
	__super::Update();

	CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();

	if (m_stateKey == "Lv" + std::to_string(m_level) + "_Idle")
	{
		if (m_attackTimer >= m_attackCooltime)
		{
			for (int i = 0; i < 3; ++i)
			{
				if (m_pSoldiers[i]->GetStateKey() == ("Lv" + std::to_string(m_level) + "_Die"))
				{
					m_stateKey = "Lv" + std::to_string(m_level) + "_SummonSoldier";
					StateChangeInit();

					m_attackTimer = 0.f;
					break;
				}
			}
		}
	}
	else if (m_stateKey == "Lv" + std::to_string(m_level) + "_SummonSoldier")
	{
		if ((int)pGC->GetAnimation()->GetCurIndex() == m_summonFrameNum &&
			(int)pGC->GetAnimation()->GetCurIndex() != pGC->GetAnimation()->GetLastFrameIndex())
		{
			for (int i = 0; i < 3; ++i)
			{
				if (m_pSoldiers[i]->GetStateKey() == ("Lv" + std::to_string(m_level) + "_Die"))
				{
					m_pSoldiers[i]->Revive();
					break;
				}
			}
		}
		else if ((int)pGC->GetAnimation()->GetCurIndex() == 0 &&
				 (int)pGC->GetAnimation()->GetCurIndex() != pGC->GetAnimation()->GetLastFrameIndex())
		{
			m_stateKey = "Lv" + std::to_string(m_level) + "_Idle";
			StateChangeInit();
		}
	}

	m_attackTimer += GET_DT();
}

void CBarrackTurret::LateUpdate(void)
{
	__super::LateUpdate();
}

void CBarrackTurret::Release(void)
{
	for (int i = 0; i < 3; ++i)
	{
		if (m_pSoldiers[i] != nullptr)
			m_pSoldiers[i]->SetNeedToBeDeleted(true);
	}
}

void CBarrackTurret::UpgradeTurret(int increase)
{
	__super::UpgradeTurret(increase);
	for (int i = 0; i < 3; ++i)
	{
		m_pSoldiers[i]->UpgradeUnit(increase);
	}
}

void CBarrackTurret::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	for (int i = 0; i < 3; ++i)
	{
		m_pSoldiers[i] = new CSoldierUnit(this);
		m_pSoldiers[i]->AddChildAndComponents();
	}
}

void CBarrackTurret::InitializeComponents(void)
{
}
