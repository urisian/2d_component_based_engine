#include "stdafx.h"
#include "PhysicsComponent.h"
#include "DataStore.h"
#include "FRC.h"
#include "PhysicsManager.h"

CPhysicsComponent::CPhysicsComponent(CObject* pOwner) :CComponent(pOwner)
{
	m_position			= D3DXVECTOR3(0, 0, 0);

	m_direction			= D3DXVECTOR3(0, 0, 0);
	m_speed				= 0.f;

	m_accel				= D3DXVECTOR3(0, 0, 0);
}


CPhysicsComponent::~CPhysicsComponent()
{
	Release();
}

void CPhysicsComponent::Initialize(void)
{
	m_position = m_pOwner->GetPosition();
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), m_pOwner->GetStateKey() + "_m_speed", m_speed);

	CPhysicsManager::GetInstance()->AddPhysicsComponent(this);
}

void CPhysicsComponent::Update(void)
{
	__super::Update();
}

void CPhysicsComponent::LateUpdate(void)
{
	__super::LateUpdate();
}

void CPhysicsComponent::Release(void)
{
}

void CPhysicsComponent::SetFromVelocity(void)
{
	m_speed = D3DXVec3Length(&m_velocity);
	m_direction = m_velocity / m_speed;
}

void CPhysicsComponent::StateChangeInit(void)
{
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), m_pOwner->GetStateKey() + "_m_speed", m_speed);
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), m_pOwner->GetStateKey() + "_m_accel", m_accel);
}
