#include "stdafx.h"
#include "CollisionComponent.h"
#include "DataStore.h"

CCollisionComponent::CCollisionComponent(CObject* pOwner) : CComponent(pOwner)
{
	m_showDebug = false;
	m_radius	= 0;

	m_position	= { 0, 0, 0 };
	m_halfExtent = { 0, 0, 0 };

	m_collisionID = COLID::END;
	m_pDebugDraw = nullptr;
}


CCollisionComponent::~CCollisionComponent()
{
}

void CCollisionComponent::Initialize(void)
{
	m_position = m_pOwner->GetParentPosition() + m_pOwner->GetPosition();
}

void CCollisionComponent::Update(void)
{
	m_position = m_pOwner->GetParentPosition() + m_pOwner->GetPosition();
}

void CCollisionComponent::LateUpdate(void)
{
}

void CCollisionComponent::Release(void)
{
}
