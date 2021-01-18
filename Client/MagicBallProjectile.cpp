#include "stdafx.h"
#include "MagicBallProjectile.h"
#include "MagicianUnit.h"
#include "PhysicsComponent.h"
#include "KillOwnerEffectComponent.h"
#include "FadeOutEffectComponent.h"
#include "CollisionComponent.h"
#include "CollisionHelper.h"
#include "Monster.h"
#include "MagicTurret.h"
#include "FRC.h"

CMagicBallProjectile::CMagicBallProjectile(CObject * pShooter) : CProjectile(pShooter)
{
	m_pShooter = pShooter;
	Initialize();
}

CMagicBallProjectile::~CMagicBallProjectile(void)
{
}

void CMagicBallProjectile::Initialize(void)
{
	__super::Initialize();

	CMagicianUnit* pShooter = static_cast<CMagicianUnit*>(m_pShooter);

	m_pTarget = pShooter->GetTarget();
	m_dmg = pShooter->GetDmg();
	m_magicDmg = pShooter->GetMagicDmg();
	m_position = pShooter->GetFinalPos();

	//if (pShooter->GetLevel() == 4)
	//{
	//	m_stateKey = "Bullet";
	//	StateChangeInit();
	//}
}

void CMagicBallProjectile::Update(void)
{
	__super::Update();
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();

	m_rotation = GetAngleFromDir(pPC->GetDirection());

	if (static_cast<CMagicianUnit*>(m_pShooter)->GetLevel() < 4)
	{
		if (m_pTarget == nullptr ||
			(m_pTarget->GetPosition().x - m_position.x) * m_direction.x < 0 ||
			(m_pTarget->GetPosition().y - m_position.y) * m_direction.y < 0 )
		{
			AddComponent<CFadeOutEffectComponent>();
		}
	}

	if (m_pTarget != nullptr)
	{
		HitTarget();


		D3DXVECTOR3 dir = m_pTarget->GetPosition() - GetFinalPos();
		D3DXVec3Normalize(&dir, &dir);
		pPC->SetDirection(dir);
		pPC->SetSpeed(pPC->GetSpeed() + 100 * GET_DT());
	}
}

void CMagicBallProjectile::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMagicBallProjectile::Release(void)
{
}

void CMagicBallProjectile::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	InitializeComponents();
}

void CMagicBallProjectile::InitializeComponents(void)
{
	CMagicianUnit* pShooter = static_cast<CMagicianUnit*>(m_pShooter);
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();
	
	if (pShooter->GetLevel() != 4)
	{
		D3DXVECTOR3 dir = m_pTarget->GetPosition() - GetFinalPos();
		D3DXVec3Normalize(&dir, &dir);
		pPC->SetDirection(dir);
		pPC->SetSpeed(10);
	}


}

void CMagicBallProjectile::HitTarget(void)
{
	__super::HitTarget();
	CCollisionComponent* pCC = GetComponent<CCollisionComponent>();
	if (m_pTarget->GetStateKey() != "Die")
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
	else
		m_pTarget = nullptr;
}

void CMagicBallProjectile::AfterHit(void)
{
	__super::AfterHit();
}
