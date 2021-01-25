#include "stdafx.h"
#include "FireRainProjectile.h"
#include "DataStore.h"
#include "InputManager.h"
#include "PhysicsComponent.h"
#include "Effect.h"
#include <ctime>
#include "CollisionManager.h"
#include "Monster.h"
#include "CollisionComponent.h"
#include "CollisionHelper.h"

CFireRainProjectile::CFireRainProjectile() : CProjectile(nullptr)
{
	Initialize();
}


CFireRainProjectile::~CFireRainProjectile()
{
	Release();
}

void CFireRainProjectile::Initialize(void)
{
	__super::Initialize();
	GET_VALUE(m_dataID, m_objectKey, "m_dmg", m_dmg);
	m_ground = CInputManager::GetInstance()->GetMousePos();
	m_position = m_ground + D3DXVECTOR3(rand() % 30, 100 + rand() % 150, 0);
	m_magicDmg = 0;
}

void CFireRainProjectile::Update(void)
{
	__super::Update();
	
}

void CFireRainProjectile::LateUpdate(void)
{
	__super::LateUpdate();
	if (m_ground.y >= m_position.y)
	{
		srand(time(nullptr));
		m_needToBeDeleted = true;
		CEffect* pEffect = new CEffect("BombBoom", "Idle", this, 0, false);
		pEffect->AddChildAndComponents();

		for (auto& monsterCC : CCollisionManager::GetInstance()->GetCollisionVector(OBJID::MONSTER))
		{
			if (monsterCC->GetOwner()->GetStateKey() != "Die")
			{
				if (D3DXVec3Length(&(monsterCC->GetOwner()->GetPosition() - m_position)) < 30)
				{
					CMonster* pMonster = static_cast<CMonster*>(monsterCC->GetOwner());

					float actualDmg = (1 - pMonster->GetArmor()) * m_dmg;
					float actualMagicDmg = (1 - pMonster->GetMR()) * m_magicDmg;

					pMonster->GetHP() -= (actualDmg + actualMagicDmg);
				}
			}
		}
	}
}

void CFireRainProjectile::Release(void)
{
}

void CFireRainProjectile::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	InitializeComponents();
}

void CFireRainProjectile::InitializeComponents(void)
{
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();
	pPC->SetDirection(D3DXVECTOR3(0, -1, 0));
}

void CFireRainProjectile::HitTarget(void)
{
}

void CFireRainProjectile::AfterHit(void)
{
}
