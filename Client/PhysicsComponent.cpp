#include "stdafx.h"
#include "PhysicsComponent.h"
#include "DataStore.h"
#include "FRC.h"

CPhysicsComponent::CPhysicsComponent(void)
{
	m_position			= D3DXVECTOR3(0, 0, 0);
	m_parentPosition	= D3DXVECTOR3(0, 0, 0);

	m_rotation			= D3DXVECTOR3(0, 0, 0);

	m_speed				= 0.f;
}


CPhysicsComponent::~CPhysicsComponent()
{
	Release();
}

void CPhysicsComponent::Initialize(void)
{
	if (m_pOwner->GetParent())
		m_parentPosition = m_pOwner->GetParent()->GetPosition();

	m_position = m_pOwner->GetPosition();
	m_rotation = m_pOwner->GetRotation();
	m_parentPosition = m_pOwner->GetParentPosition();
	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), "m_speed", m_speed);
}

void CPhysicsComponent::Update(void)
{
	m_parentPosition = m_pOwner->GetParentPosition();
	m_position += GetDirFromAngle(m_rotation.z) * m_speed * GET_DT();

	m_pOwner->SetPosition(m_position);
	m_pOwner->SetRotation(m_rotation);
}

void CPhysicsComponent::LateUpdate(void)
{
}

void CPhysicsComponent::Release(void)
{
}
