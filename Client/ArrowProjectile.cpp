#include "stdafx.h"
#include "ArrowProjectile.h"
#include "PhysicsComponent.h"
#include "ArcherTurret.h"
#include "ArcherUnit.h"
#include "FRC.h"
#include "Monster.h"
#include "GraphicsComponent.h"
#include "CollisionComponent.h"
#include "CollisionHelper.h"
#include "KillOwnerEffectComponent.h"
#include "Animation.h"

CArrowProjectile::CArrowProjectile(CObject* pShooter) : CProjectile(pShooter)
{
	Initialize();
}


CArrowProjectile::~CArrowProjectile()
{
	Release();
}

void CArrowProjectile::Initialize(void)
{
	__super::Initialize();

	CArcherUnit* pShooter = static_cast<CArcherUnit*>(m_pShooter);

	m_pTarget	= pShooter->GetTarget();
	m_dmg		= pShooter->GetDmg();
	m_magicDmg	= pShooter->GetMagicDmg();
	m_position	= pShooter->GetFinalPos();

	if (pShooter->GetLevel() == 4)
	{
		m_stateKey = "Bullet";
		StateChangeInit();
	}
}

void CArrowProjectile::Update(void)
{
	__super::Update();
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();	

	m_rotation = GetAngleFromDir(pPC->GetDirection());

	if (static_cast<CArcherUnit*>(m_pShooter)->GetLevel() < 4)
	{
		if (m_pTarget == nullptr)
		{
			if (m_position.y < m_ground.y && m_direction.y < 0)
			{
				m_stateKey = "Done";
				StateChangeInit();
				AddComponent<CKillOwnerEffectComponent>();
			}
		}
		else if (m_position.y < m_pTarget->GetFinalPos().y && m_direction.y < 0)
		{
			m_stateKey = "Done";
			StateChangeInit();
			AddComponent<CKillOwnerEffectComponent>();
		}
	}
	else
	{
		if (m_pTarget == nullptr)
			AddComponent<CKillOwnerEffectComponent>();
	}

	if (m_pTarget != nullptr)
		HitTarget();
}

void CArrowProjectile::LateUpdate(void)
{
	__super::LateUpdate();
}

void CArrowProjectile::Release(void)
{
}

void CArrowProjectile::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	InitializeComponents();
}

void CArrowProjectile::InitializeComponents(void)
{
	CArcherUnit* pShooter = static_cast<CArcherUnit*>(m_pShooter);
	CGraphicsComponent* pShooterGC = pShooter->GetComponent<CGraphicsComponent>();
	float duration = pShooter->GetAttackFrameNum() / pShooterGC->GetAnimation()->GetAniSecPerFrame();//static_cast<CArcherTurret*>(pShooter->GetParent())->GetAttackCooltime();
	D3DXVECTOR3 targetPos = m_pTarget->GetFinalPos() + m_pTarget->GetDirection() * m_pTarget->GetComponent<CPhysicsComponent>()->GetSpeed() * duration;


	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();

	if (pShooter->GetLevel() < 4)
	{
		pPC->SetAccel(D3DXVECTOR3(0, -1600, 0));
		pPC->SetVelocity((targetPos - GetPosition()) / duration - 0.5f * pPC->GetAccel() * duration);
		pPC->SetFromVelocity();
	}
	else
	{
		duration = 0.1f;
		targetPos = m_pTarget->GetFinalPos() + m_pTarget->GetDirection() * m_pTarget->GetComponent<CPhysicsComponent>()->GetSpeed() * duration;
		pPC->SetVelocity((targetPos - GetPosition()) / duration);
		pPC->SetFromVelocity();
	}
}

void CArrowProjectile::HitTarget(void)
{
	__super::HitTarget();
	CCollisionComponent* pCC = GetComponent<CCollisionComponent>();
	if (m_pTarget->GetStateKey() != "Die")
	{
		if (m_direction.y < 0 || static_cast<CArcherUnit*>(m_pShooter)->GetLevel() == 4)
		{
			if (CollisionHelper::PointCircleCollision(pCC, m_pTarget->GetComponent<CCollisionComponent>()))
			{
				CMonster* pMonster = static_cast<CMonster*>(m_pTarget);

				float actualDmg = (1 - pMonster->GetArmor()) * m_dmg;
				float actualMagicDmg = (1 - pMonster->GetMR()) * m_magicDmg;

				pMonster->GetHP() -= (actualDmg + actualMagicDmg);

				AfterHit();
			}
		}
	}
	else
	{
		m_ground = m_pTarget->GetFinalPos();
		m_pTarget = nullptr;
	}

}

void CArrowProjectile::AfterHit(void)
{
	__super::AfterHit();
}
