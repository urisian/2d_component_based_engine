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
#include "Effect.h"
#include "GraphicsComponent.h"
#include "Animation.h"

CMagicBallProjectile::CMagicBallProjectile(CObject * pShooter) : CProjectile(pShooter)
{
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
	if (pShooter->GetLevel() == 3)
	{
		m_stateKey = "Fire";
		StateChangeInit();
	}
	if (pShooter->GetLevel() == 4)
	{
		m_stateKey = "Laser";
		StateChangeInit();

		m_position = (m_position + m_pTarget->GetFinalPos()) / 2.f;
		m_size.x = D3DXVec3Length(&(m_pTarget->GetFinalPos() - pShooter->GetFinalPos()));
		m_size.y = 10.f;
		m_rotation = GetAngleFromDir(m_pTarget->GetFinalPos() - pShooter->GetFinalPos());
	}
}

void CMagicBallProjectile::Update(void)
{
	__super::Update();
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();
	CMagicianUnit* pShooter = static_cast<CMagicianUnit*>(m_pShooter);

	if (pShooter->GetLevel() != 4)
	{
		m_rotation = GetAngleFromDir(pPC->GetDirection());


		if (m_pTarget == nullptr)
			AddComponent<CFadeOutEffectComponent>();
		if (m_pTarget != nullptr)
		{
			HitTarget();


			D3DXVECTOR3 dir = m_pTarget->GetPosition() - GetFinalPos();
			D3DXVec3Normalize(&dir, &dir);
			pPC->SetDirection(dir);
			pPC->SetSpeed(pPC->GetSpeed() + 100 * GET_DT());
		}
	}
	else
	{
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

		if (m_pTarget == nullptr || m_stateKey == "Idle")
			m_needToBeDeleted = true;
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
	

	if (pShooter->GetLevel() != 4)
	{
		CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();
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
		if (static_cast<CMagicianUnit*>(m_pShooter)->GetLevel() != 4)
		{
			if (CollisionHelper::PointCircleCollision(pCC, m_pTarget->GetComponent<CCollisionComponent>()))
			{
				GiveDamage();
				CEffect* pEffect;
				if (static_cast<CMagicianUnit*>(m_pShooter)->GetLevel() == 3)
					pEffect = new CEffect("MagicBoom", "Fire", m_pTarget, 0, false);
				else
					pEffect = new CEffect("MagicBoom", "Idle", m_pTarget, 0, false);
				pEffect->AddChildAndComponents();

				AfterHit();
			}
		}
		else
		{
			GiveDamage();
			CEffect* pEffect = new CEffect("MagicBoom", "Dark", m_pTarget, 0, false);
			pEffect->AddChildAndComponents();
		}

	}
	else
		m_pTarget = nullptr;
}

void CMagicBallProjectile::AfterHit(void)
{
	__super::AfterHit();
}


