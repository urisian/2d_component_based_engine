#include "stdafx.h"
#include "Monster.h"
#include "DataStore.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "FRC.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_objID = OBJID::MONSTER;
	m_dataID = DATAID::MONSTER;

	__super::Initialize();

	m_routeIndex = 0;
	m_pTarget = nullptr;

	CMonster::ReadDataFromStore();
}

void CMonster::Update(void)
{
	__super::Update();
	if (m_routeIndex < m_pRouteInfo->routePoints.size())
	{
		D3DXVECTOR3 distanceFromCurGoal = m_pRouteInfo->routePoints[m_routeIndex] - m_position;
		if (D3DXVec3Length(&distanceFromCurGoal) <= GetComponent<CPhysicsComponent>()->GetSpeed() * GET_DT())
		{
			m_position = m_pRouteInfo->routePoints[m_routeIndex];
			++m_routeIndex;
		}
		if (m_routeIndex < m_pRouteInfo->routePoints.size())
			D3DXVec3Normalize(&GetComponent<CPhysicsComponent>()->GetDirection(), 
							  &(m_pRouteInfo->routePoints[m_routeIndex] - m_position));
	}

	if (m_hp <= 0)
		Die();

}

void CMonster::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMonster::Release(void)
{
}

void CMonster::AddChildAndComponents(void)
{
	AddComponent<CGraphicsComponent>();
	AddComponent<CPhysicsComponent>();
	AddComponent<CCollisionComponent>();
}

void CMonster::ReadDataFromStore(void)
{
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_numOfSkill", m_numOfSkill);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_attackRange", m_attackRange);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_attackCooltime", m_attackCooltime);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_attackFrameNum", m_attackFrameNum);

	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_dmg", m_dmg);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_magicDmg", m_magicDmg);

	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_hp", m_hp);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_armor", m_armor);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_mr", m_mr);
}

void CMonster::Die(void)
{
}
