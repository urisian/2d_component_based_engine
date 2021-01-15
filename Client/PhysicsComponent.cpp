#include "stdafx.h"
#include "PhysicsComponent.h"
#include "DataStore.h"
#include "FRC.h"

CPhysicsComponent::CPhysicsComponent(CObject* pOwner) :CComponent(pOwner)
{
	m_position			= D3DXVECTOR3(0, 0, 0);

	m_direction			= D3DXVECTOR3(0, 0, 0);

	m_speed				= 0.f;
}


CPhysicsComponent::~CPhysicsComponent()
{
	Release();
}

void CPhysicsComponent::Initialize(void)
{
	m_position = m_pOwner->GetPosition();
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), m_pOwner->GetStateKey() + "_m_speed", m_speed);
}

void CPhysicsComponent::Update(void)
{
	m_position += m_direction * m_speed * GET_DT();

	m_pOwner->SetPosition(m_position);
	m_pOwner->SetDirection(m_direction);
}

void CPhysicsComponent::LateUpdate(void)
{
}

void CPhysicsComponent::Release(void)
{
}

void CPhysicsComponent::StateChangeInit(void)
{
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), m_pOwner->GetStateKey() + "_m_speed", m_speed);
}
