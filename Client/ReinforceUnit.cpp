#include "stdafx.h"
#include "ReinforceUnit.h"
#include "InputManager.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "Monster.h"
#include "FRC.h"
#include "CollisionComponent.h"
#include "Animation.h"
#include "Effect.h"
#include "KillOwnerEffectComponent.h"
#include "CollisionManager.h"
CReinforceUnit::CReinforceUnit(int id)
{
	m_rallyPosition = CInputManager::GetInstance()->GetMousePos();
	m_lifeTime = 30;
	m_id = id;

	Initialize();
}


CReinforceUnit::~CReinforceUnit()
{
}

void CReinforceUnit::Initialize(void)
{
	__super::Initialize();

	float angle = D3DXToRadian(m_id * 180.f);

	m_position = m_rallyPosition + D3DXVECTOR3(cosf(angle), sinf(angle), 0) * 12.f;
	m_rallyPosition = m_position;
}

void CReinforceUnit::Update(void)
{
	__super::Update();
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();
	CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();
	CMonster* pMonster = static_cast<CMonster*>(m_pTarget);

	if (m_stateKey == "ToRally")
		MoveTo(m_rallyPosition, "Idle");
	else if (m_stateKey == "ToEnemy")
	{
		MoveTo(m_approachPosition, "Attack");
	}
	else if (m_stateKey == "Attack")
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
	else if (m_stateKey == "Die")
		AddComponent<CKillOwnerEffectComponent>()->SetLifeTime(2);

	if ((m_hp < 0 || m_lifeTime < 0)&& m_stateKey != "Die")
	{
		if(pGC->GetAnimation() != nullptr)
			pGC->GetAnimation()->SetRepeat(false);
		m_pTarget = nullptr;
		pMonster->SetTarget(nullptr);

		m_stateKey = "Die";
		StateChangeInit();
	}

	m_lifeTime -= GET_DT();
}

void CReinforceUnit::LateUpdate(void)
{
	__super::LateUpdate();

	if (m_stateKey == "Idle" ||
		m_stateKey == "Attack" ||
		m_stateKey == "ToEnemy")
		FindTarget();
}

void CReinforceUnit::Release(void)
{
}

void CReinforceUnit::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	AddComponent<CPhysicsComponent>();
	AddComponent<CCollisionComponent>();
}

void CReinforceUnit::InitializeComponents(void)
{
}

void CReinforceUnit::StateChangeInit(void)
{
	__super::StateChangeInit();
}

void CReinforceUnit::FindTarget(void)
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

						m_stateKey = "ToEnemy";
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
				m_stateKey = "ToRally";
				StateChangeInit();
			}
			else
			{
				m_stateKey = "Idle";
				StateChangeInit();
			}
		}
		else
		{
			m_stateKey = "ToEnemy";
			StateChangeInit();

			m_approachPosition = D3DXVECTOR3(m_pTarget->GetPosition().x - m_size.x / 2, m_pTarget->GetPosition().y, 0);
		}
	}
	else if (static_cast<CMonster*>(m_pTarget)->GetTarget() != this)
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

						m_stateKey = "ToEnemy";
						StateChangeInit();

						m_approachPosition = D3DXVECTOR3(m_pTarget->GetPosition().x - m_size.x / 2, m_pTarget->GetPosition().y, 0);
						return;
					}
				}
			}
		}
	}
}

void CReinforceUnit::MoveTo(D3DXVECTOR3 destPos, std::string nextStateKey)
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
