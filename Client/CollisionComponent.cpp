#include "stdafx.h"
#include "CollisionComponent.h"
#include "DataStore.h"
#include "CollisionManager.h"

CCollisionComponent::CCollisionComponent(CObject* pOwner) : CComponent(pOwner)
{
	m_showDebug = false;
	m_radius	= 0;

	m_position	= { 0, 0, 0 };
	m_halfExtent = { 0, 0, 0 };

	m_pDebugDraw = nullptr;
}


CCollisionComponent::~CCollisionComponent()
{
}

void CCollisionComponent::Initialize(void)
{
	__super::Initialize();

	CCollisionManager::GetInstance()->AddCollisionComponent(this);
}

void CCollisionComponent::Update(void)
{
	__super::Update();

	m_position = m_pOwner->GetParentPosition() + m_pOwner->GetPosition();
}

void CCollisionComponent::LateUpdate(void)
{
}

void CCollisionComponent::Release(void)
{
}

void CCollisionComponent::StateChangeInit(void)
{
}
