#include "stdafx.h"
#include "Projectile.h"
#include "Turret.h"
#include "GraphicsComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "CollisionManager.h"
#include "CollisionHelper.h"
#include "Monster.h"
#include "Effect.h"

CProjectile::CProjectile(CObject* pShooter)
{
	m_pShooter = pShooter;
}


CProjectile::~CProjectile()
{
	Release();
}

void CProjectile::Initialize(void)
{
	m_objID = OBJID::PROJECTILE;
	m_dataID = DATAID::PROJECTILE;

	
	__super::Initialize();
}

void CProjectile::Update(void)
{
	__super::Update();
}

void CProjectile::LateUpdate(void)
{
	__super::LateUpdate();
}

void CProjectile::Release(void)
{
}

void CProjectile::AddChildAndComponents(void)
{
	AddComponent<CGraphicsComponent>();
	AddComponent<CPhysicsComponent>();
	AddComponent<CCollisionComponent>();
}

void CProjectile::HitTarget(void)
{
}

void CProjectile::AfterHit(void)
{
	m_needToBeDeleted = true;
	CEffect* pEffect = new CEffect("BloodDrop", "Idle", m_pTarget, 0, false);
	pEffect->AddChildAndComponents();
}

void CProjectile::GiveDamage(void)
{
	CMonster* pMonster = static_cast<CMonster*>(m_pTarget);

	float actualDmg = (1 - pMonster->GetArmor()) * m_dmg;
	float actualMagicDmg = (1 - pMonster->GetMR()) * m_magicDmg;

	pMonster->GetHP() -= (actualDmg + actualMagicDmg);
}
