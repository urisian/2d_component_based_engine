#include "stdafx.h"
#include "CollisionComponent.h"
#include "DataStore.h"
#include "CollisionManager.h"

CCollisionComponent::CCollisionComponent(CObject* pOwner) : CComponent(pOwner)
{
	m_showDebug = false;
	m_pDebugDraw = nullptr;

	m_position = { 0, 0, 0 };
	
	m_radius	= 0;	
	m_halfExtent = { 0, 0, 0 };
}


CCollisionComponent::~CCollisionComponent()
{
}

void CCollisionComponent::Initialize(void)
{
	__super::Initialize();
	
	m_halfExtent = m_pOwner->GetSize() / 2.f;
	m_radius = (m_halfExtent.x < m_halfExtent.y) ? m_halfExtent.x : m_halfExtent.y;
	
	
	CCollisionManager::GetInstance()->AddCollisionComponent(this);
}

void CCollisionComponent::Update(void)
{
	__super::Update();
}

void CCollisionComponent::LateUpdate(void)
{
	__super::LateUpdate();

	m_position = m_pOwner->GetFinalPos();
}

void CCollisionComponent::Release(void)
{
}

void CCollisionComponent::StateChangeInit(void)
{
	m_halfExtent = m_pOwner->GetSize() / 2.f;
	m_radius = (m_halfExtent.x < m_halfExtent.y) ? m_halfExtent.x : m_halfExtent.y;
}
