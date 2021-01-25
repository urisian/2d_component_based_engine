#include "stdafx.h"
#include "BarrackTurret.h"
#include "FRC.h"
#include "SoldierUnit.h"
#include "GraphicsComponent.h"
#include "Animation.h"
#include "DataStore.h"
#include "Decoration.h"
#include "ClickableComponent.h"
#include "InputManager.h"

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

	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_summonFrameNum", m_summonFrameNum);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_soldierHP", m_soldierHP);
	m_checkRally = false;
	m_attackTimer = 0.f;
	m_anyRevive = false;
}

void CBarrackTurret::Update(void)
{
	__super::Update();

	CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();

	if(m_checkRally)
	{
		if (m_stateKey == "Lv" + std::to_string(m_level) + "_Idle")
		{
			if (m_attackTimer >= m_attackCooltime)
			{
				for (int i = 0; i < 3; ++i)
				{
					if (m_pSoldiers[i]->GetStateKey() == ("Lv" + std::to_string(m_level) + "_WaitRevive"))
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
				if(m_attackTimer < 1)
					pGC->GetAnimation()->SetStatus(ANIMATION::STATUS::PAUSE);
				else
					pGC->GetAnimation()->SetStatus(ANIMATION::STATUS::PLAY);
				for (int i = 0; i < 3; ++i)
				{
					if (!m_anyRevive && m_pSoldiers[i]->GetStateKey() == ("Lv" + std::to_string(m_level) + "_WaitRevive"))
					{
						m_pSoldiers[i]->Revive();
						m_anyRevive = true;
						break;
					}
				}
			}
			else if ((int)pGC->GetAnimation()->GetCurIndex() == 0 &&
				(int)pGC->GetAnimation()->GetCurIndex() != pGC->GetAnimation()->GetLastFrameIndex())
			{
				m_stateKey = "Lv" + std::to_string(m_level) + "_Idle";
				m_anyRevive = false;
				StateChangeInit();
			}
		}

		m_attackTimer += GET_DT();
	}
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
	m_pRangeCircle->SetSize(D3DXVECTOR3(m_rallyRange, m_rallyRange * 0.6f, 0));
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_summonFrameNum", m_summonFrameNum);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_soldierHP", m_soldierHP);
}

void CBarrackTurret::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();

	MakeSoldier();
	MakeRallyCircle();
}

void CBarrackTurret::InitializeComponents(void)
{
}


void CBarrackTurret::SetRallyPoint(void)
{
	m_rallyPoint = CInputManager::GetInstance()->GetMousePos();
	m_pRallyCircle->SetActivated(false);
	m_checkRally = true;

	for (int i = 0; i < 3; ++i)
	{
		m_pSoldiers[i]->SetActivated(true);
		m_pSoldiers[i]->SetRallyPosition(m_rallyPoint);
		m_pSoldiers[i]->SetRallyChanged(true);
	}
}

void CBarrackTurret::MakeSoldier(void)
{
	for (int i = 0; i < 3; ++i)
	{
		m_pSoldiers[i] = new CSoldierUnit(this);

		m_pSoldiers[i]->SetID(i);
		m_pSoldiers[i]->AddChildAndComponents();
		m_pSoldiers[i]->SetStateKey("Lv" + std::to_string(m_pSoldiers[i]->GetLevel()) + "_Revived");
		m_pSoldiers[i]->StateChangeInit();
		m_pSoldiers[i]->SetActivated(false);
	}
}

void CBarrackTurret::MakeRallyCircle(void)
{
	m_pRallyCircle = new CDecoration("RangeCircle", "Blue", this);
	m_pRallyCircle->AddChildAndComponents();
	m_pRallyCircle->AddComponent<CClickableComponent>()->SetPlayFunc(std::bind(&CBarrackTurret::SetRallyPoint, this));
	m_pRallyCircle->SetSize(D3DXVECTOR3(m_rallyRange, m_rallyRange * 0.6f, 0));
	m_pRallyCircle->SetActivated(false);
}
