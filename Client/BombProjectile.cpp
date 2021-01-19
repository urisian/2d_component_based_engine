#include "stdafx.h"
#include "BombProjectile.h"
#include "BombTurret.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "CollisionManager.h"
#include "CollisionHelper.h"
#include "CollisionComponent.h"
#include "Monster.h"
#include "Effect.h"
#include "Animation.h"

CBombProjectile::CBombProjectile(CObject* pShooter) : CProjectile(pShooter)
{
	Initialize();
}


CBombProjectile::~CBombProjectile()
{
	Release();
}

void CBombProjectile::Initialize(void)
{
	CBombTurret* pShooter = static_cast<CBombTurret*>(m_pShooter);

	m_stateKey = "Lv" + std::to_string(pShooter->GetLevel()) + "_Idle";

	__super::Initialize();
	
	m_pTarget = pShooter->GetTarget();
	m_dmg = pShooter->GetDmg();
	m_magicDmg = pShooter->GetMagicDmg();
	

	if (pShooter->GetLevel() != 4)
	{
		m_position = pShooter->GetFinalPos();
		m_ground = m_pTarget->GetFinalPos();
	}
	else
	{
		m_position = (m_position + m_pTarget->GetFinalPos()) / 2.f;
		m_size.x = D3DXVec3Length(&(m_pTarget->GetFinalPos() - pShooter->GetFinalPos()));
		m_size.y = 25.f;
		m_rotation = GetAngleFromDir(m_pTarget->GetFinalPos() - pShooter->GetFinalPos());
	}
}

void CBombProjectile::Update(void)
{
	__super::Update();
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();
	CBombTurret* pShooter = static_cast<CBombTurret*>(m_pShooter);

	if (m_stateKey == "Lv4_Idle")
	{
		if (m_pTarget == nullptr || pShooter->GetTarget() == nullptr)
			return;
			//m_needToBeDeleted = true;
		if (m_pTarget != nullptr)
		{
			if (m_pTarget != pShooter->GetTarget())
				m_needToBeDeleted = true;

			pPC->SetPosition((pShooter->GetFinalPos() + m_pTarget->GetFinalPos()) / 2.f);
			m_size.x = D3DXVec3Length(&(m_pTarget->GetFinalPos() - pShooter->GetFinalPos()));
			m_rotation = GetAngleFromDir(m_pTarget->GetFinalPos() - pShooter->GetFinalPos());

			if (GetComponent<CGraphicsComponent>()->GetAnimation()->GetCurIndex() == 0)
				HitTarget();
		}

		

	}
	else
		HitTarget();
}

void CBombProjectile::LateUpdate(void)
{
	__super::LateUpdate();
}

void CBombProjectile::Release(void)
{
}

void CBombProjectile::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	InitializeComponents();
}

void CBombProjectile::InitializeComponents(void)
{
	CBombTurret* pShooter = static_cast<CBombTurret*>(m_pShooter);
	if (pShooter->GetLevel() != 4)
	{

		CGraphicsComponent* pShooterGC = pShooter->GetComponent<CGraphicsComponent>();
		float duration = 0.5;
		D3DXVECTOR3 targetPos = m_pTarget->GetFinalPos();

		CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();


		pPC->SetAccel(D3DXVECTOR3(0, -1600, 0));
		pPC->SetVelocity((targetPos - GetPosition()) / duration - 0.5f * pPC->GetAccel() * duration);
		pPC->SetFromVelocity();
	}
}

void CBombProjectile::HitTarget(void)
{
	__super::HitTarget();
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();

	CBombTurret* pShooter = static_cast<CBombTurret*>(m_pShooter);
	if (pShooter->GetLevel() != 4)
	{
		if (m_direction.y < 0)
		{
			if (m_position.y < m_ground.y)
			{
				m_position = m_ground;

				for (auto& monsterCC : CCollisionManager::GetInstance()->GetCollisionVector(OBJID::MONSTER))
				{
					if (monsterCC->GetOwner()->GetStateKey() != "Die")
					{
						if (CollisionHelper::PointEclipseCollision(monsterCC->GetPosition(),
							m_position + m_parentPosition,
							m_explodeRange))
						{
							CMonster* pMonster = static_cast<CMonster*>(monsterCC->GetOwner());

							float actualDmg = (1 - pMonster->GetArmor()) * m_dmg;
							float actualMagicDmg = (1 - pMonster->GetMR()) * m_magicDmg;

							pMonster->GetHP() -= (actualDmg + actualMagicDmg);
						}
					}
				}

				AfterHit();
			}
		}
	}
	else
	{
		if (m_pTarget != nullptr && m_pTarget->GetStateKey() != "Die")
		{
			GiveDamage();
		}
		else
			m_pTarget = nullptr;
	}
}

void CBombProjectile::AfterHit(void)
{
	CEffect* pEffect = new CEffect("BombBoom", "Idle", this, 0, false);
	pEffect->AddChildAndComponents();
	m_needToBeDeleted = true;
}







