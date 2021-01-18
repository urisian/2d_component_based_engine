#include "stdafx.h"
#include "PhysicsManager.h"
#include "PhysicsComponent.h"
#include "FRC.h"

CPhysicsManager* CPhysicsManager::m_s_pInstance = nullptr;

CPhysicsManager * CPhysicsManager::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CPhysicsManager;

	return m_s_pInstance;
}

void CPhysicsManager::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CPhysicsManager::Initialize(void)
{
}

void CPhysicsManager::Update(void)
{
	for (auto& it = m_vPhysicsComponents.begin(); it != m_vPhysicsComponents.end(); )
	{
		if ((*it)->GetActivated() && !(*it)->GetNeedToBeDeleted())
			(*it)->Update();

		if ((*it)->GetNeedToBeDeleted())
		{
			SAFE_DELETE(*it);
			it = m_vPhysicsComponents.erase(it);
		}
		else
			++it;
	}
}

void CPhysicsManager::LateUpdate(void)
{
	for (auto& element : m_vPhysicsComponents)
	{
		if (!element->GetNeedToBeDeleted() && element->GetOwner()->GetActivated())
		{
			element->SetVelocity(element->GetSpeed() * element->GetDirection());
			element->GetVelocity() += element->GetAccel() * GET_DT();

			element->SetFromVelocity();

			element->GetPosition() += element->GetVelocity() * GET_DT();

			element->GetOwner()->SetPosition(element->GetPosition());
			element->GetOwner()->SetDirection(element->GetDirection());
		}
	}
}

void CPhysicsManager::Release(void)
{
	for (auto& physicsComponent : m_vPhysicsComponents)
		SafeDelete(physicsComponent);
}

void CPhysicsManager::AddPhysicsComponent(CPhysicsComponent * pPC)
{
	m_vPhysicsComponents.push_back(pPC);
}

CPhysicsManager::CPhysicsManager()
{
}


CPhysicsManager::~CPhysicsManager()
{
	Release();
}