#include "stdafx.h"
#include "SoldierUnit.h"
#include "BarrackTurret.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "CollisionHelper.h"
#include "CollisionManager.h"
#include "Monster.h"
#include "GraphicsComponent.h"
#include "Animation.h"
#include "FadeOutEffectComponent.h"
#include "FRC.h"
#include "Effect.h"

CSoldierUnit::CSoldierUnit(CObject* pBarrackTurret)
{
	m_pParent = pBarrackTurret;
	
	Initialize();

	//CObject::Initialize에서 세팅해주는 것 초기화.
	m_parentPosition = D3DXVECTOR3(0, 0, 0);
	m_approachPosition = D3DXVECTOR3(0, 0, 0);
	m_reviveTimer = 0.f;
	m_id = 0;
}


CSoldierUnit::~CSoldierUnit()
{
}

void CSoldierUnit::Initialize(void)
{
	__super::Initialize();
	SetPosition(m_pParent->GetFinalPos());
}

void CSoldierUnit::Update(void)
{
	__super::Update();
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();
	CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();
	CMonster* pMonster = static_cast<CMonster*>(m_pTarget);

	if (m_rallyChanged == true)
	{
		m_stateKey = "Lv" + std::to_string(m_level) + "_ToRally";
		
		if (m_pTarget != nullptr && pMonster->GetTarget() == this)
			pMonster->SetTarget(nullptr);
		m_pTarget = nullptr;

		StateChangeInit();
		m_rallyChanged = false;
	}

	if (m_stateKey == "Lv" + std::to_string(m_level) + "_ToRally")
		MoveTo(m_rallyPosition, "Lv" + std::to_string(m_level) + "_Idle");
	else if (m_stateKey == "Lv" + std::to_string(m_level) + "_Idle")
	{
	}
	else if (m_stateKey == "Lv" + std::to_string(m_level) + "_ToEnemy")
	{
		MoveTo(m_approachPosition, "Lv" + std::to_string(m_level) + "_Attack");
	}
	else if (m_stateKey == "Lv" + std::to_string(m_level) + "_Attack")
	{
		pGC->SetXFlip(false);
		if ((int)pGC->GetAnimation()->GetCurIndex() == m_attackFrameNum &&
			(int)pGC->GetAnimation()->GetCurIndex() != pGC->GetAnimation()->GetLastFrameIndex())
		{
			float actualDmg = (1 - pMonster->GetArmor()) * m_dmg;
			float actualMagicDmg = (1 - pMonster->GetMR()) * m_magicDmg;

			pMonster->GetHP() -= (actualDmg + actualMagicDmg);
			CEffect* pEffect = new CEffect("BloodDrop", "Idle", m_pTarget, 0, false);
			pEffect->AddChildAndComponents();
		}
	}
	else if (m_stateKey == "Lv" + std::to_string(m_level) + "_Die")
	{
		if (pGC->GetColor().a <= 0)
		{
			pGC->GetColor().a = 1.f;
			m_hp = static_cast<CBarrackTurret*>(m_pParent)->GetSoldierHP();
			pPC->SetPosition(m_pParent->GetFinalPos());
			m_stateKey = "Lv" + std::to_string(m_level) + "_WaitRevive";
			pGC->GetAnimation()->SetRepeat(true);
			StateChangeInit();
			m_activated = false;
		}
	}
	else if (m_stateKey == "Lv" + std::to_string(m_level) + "_Revived")
		MoveTo(m_pParent->GetFinalPos() - D3DXVECTOR3(0, 30, 0), "Lv" + std::to_string(m_level) + "_ToRally");

	//다시 살릴떄 리피트 켜라
	if (m_hp < 0 && m_stateKey != "Lv" + std::to_string(m_level) + "_Die")
	{
		pGC->GetAnimation()->SetRepeat(false);
		AddComponent<CFadeOutEffectComponent>()->SetKillOwner(false);
		m_pTarget = nullptr;
		pMonster->SetTarget(nullptr);

		m_stateKey = "Lv" + std::to_string(m_level) + "_Die";
		StateChangeInit();
	}


}

void CSoldierUnit::LateUpdate(void)
{
	__super::LateUpdate();
	if(m_stateKey == "Lv" + std::to_string(m_level) + "_Idle" ||
		m_stateKey == "Lv" + std::to_string(m_level) + "_Attack" ||
		m_stateKey == "Lv" + std::to_string(m_level) + "_ToEnemy")
		FindTarget();
}

void CSoldierUnit::Release(void)
{
}

void CSoldierUnit::UpgradeUnit(int increase)
{
	__super::UpgradeUnit(increase);
}

void CSoldierUnit::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	AddComponent<CPhysicsComponent>();
	AddComponent<CCollisionComponent>();
}

void CSoldierUnit::InitializeComponents(void)
{
}

void CSoldierUnit::StateChangeInit(void)
{
	__super::StateChangeInit();
}

void CSoldierUnit::Revive(void)
{
	m_activated = true;
	m_stateKey = "Lv" + std::to_string(m_level) + "_Revived";
	StateChangeInit();
}

void CSoldierUnit::SetRallyPosition(D3DXVECTOR3 rallyPoint)
{
	float angle = D3DXToRadian(m_id * 120.f);

	m_rallyPosition = rallyPoint + D3DXVECTOR3(cosf(angle), sinf(angle), 0) * 12.f;
}

void CSoldierUnit::FindTarget(void)
{
	if (m_pTarget != nullptr && m_pTarget->GetStateKey() == "Die")
		m_pTarget = nullptr;

	if (m_pTarget == nullptr)
	{
		for (auto& monsterCC : CCollisionManager::GetInstance()->GetCollisionVector(OBJID::MONSTER))
		{
			if (monsterCC->GetOwner()->GetStateKey() != "Die")
			{
				if (D3DXVec3Length(&(monsterCC->GetPosition() - m_position)) < m_attackRange)
				{
					m_pTarget = monsterCC->GetOwner();
					if (static_cast<CMonster*>(m_pTarget)->GetTarget() == nullptr)
					{
						static_cast<CMonster*>(m_pTarget)->SetTarget(this);

						m_stateKey = "Lv" + std::to_string(m_level) + "_ToEnemy";
						StateChangeInit();

						m_approachPosition = D3DXVECTOR3(m_pTarget->GetPosition().x - m_size.x / 2, m_pTarget->GetPosition().y, 0);
						return;
					}
				}
			}
		}

		if (m_pTarget == nullptr)
		{
			if (m_position != m_rallyPosition)
			{
				m_stateKey = "Lv" + std::to_string(m_level) + "_ToRally";
				StateChangeInit();
			}
			else
			{
				m_stateKey = "Lv" + std::to_string(m_level) + "_Idle";
				StateChangeInit();
			}
		}
		else
		{
			m_stateKey = "Lv" + std::to_string(m_level) + "_ToEnemy";
			StateChangeInit();

			m_approachPosition = D3DXVECTOR3(m_pTarget->GetPosition().x - m_size.x / 2, m_pTarget->GetPosition().y, 0);
		}
	}
	else if(static_cast<CMonster*>(m_pTarget)->GetTarget() != this)
	{
		for (auto& monsterCC : CCollisionManager::GetInstance()->GetCollisionVector(OBJID::MONSTER))
		{
			if (monsterCC->GetOwner()->GetStateKey() != "Die")
			{
				if (D3DXVec3Length(&(monsterCC->GetPosition() - m_position)) < 50)
				{
					m_pTarget = monsterCC->GetOwner();
					if (static_cast<CMonster*>(m_pTarget)->GetTarget() == nullptr)
					{
						static_cast<CMonster*>(m_pTarget)->SetTarget(this);

						m_stateKey = "Lv" + std::to_string(m_level) + "_ToEnemy";
						StateChangeInit();

						m_approachPosition = D3DXVECTOR3(m_pTarget->GetPosition().x - m_size.x / 2, m_pTarget->GetPosition().y, 0);
						return;
					}
				}
			}
		}
	}

	
}

void CSoldierUnit::MoveTo(D3DXVECTOR3 destPos, std::string nextStateKey)
{
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();
	CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();

	if (pPC->GetDirection().x < 0)
		pGC->SetXFlip(true);
	else
		pGC->SetXFlip(false);

	
	D3DXVec3Normalize(&m_direction, &(destPos - m_position));
	pPC->SetDirection(m_direction);

	if (D3DXVec3Length(&(destPos - m_position)) < pPC->GetSpeed() * GET_DT())
	{
		pPC->SetPosition(destPos);
		m_stateKey = nextStateKey;
		StateChangeInit();
	}
}


