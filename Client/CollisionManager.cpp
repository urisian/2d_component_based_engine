#include "stdafx.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "CollisionComponent.h"
#include "ClickableComponent.h"
#include "GameInfo.h"

CCollisionManager* CCollisionManager::m_s_pInstance = nullptr;



CCollisionManager * CCollisionManager::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CCollisionManager;

	return m_s_pInstance;
}

void CCollisionManager::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CCollisionManager::Initialize(void)
{
}

void CCollisionManager::Update(void)
{
	bool anyClick = false;

	std::sort(m_vClickableComponent.begin(),
			  m_vClickableComponent.end(), 
			  [](CClickableComponent* pCC1, CClickableComponent* pCC2)
				{
					return pCC1->GetCOrder() < pCC2->GetCOrder();
				});


	for (unsigned int i = 0; i < m_vClickableComponent.size(); ++i)
	{
		if (!m_vClickableComponent[i]->GetNeedToBeDeleted() && m_vClickableComponent[i]->GetOwner()->GetActivated())
		{
			m_vClickableComponent[i]->Update();

			if (m_vClickableComponent[i]->GetClickUp())
			{
				anyClick = true;
				break;
			}
		}
	}


	if (IMKEY_UP(MOUSE_LEFT) && !anyClick)
		CGameInfo::GetInstance()->SetFocusedObject(nullptr);
}

void CCollisionManager::LateUpdate(void)
{
	for (auto& it = m_vClickableComponent.begin(); it != m_vClickableComponent.end();)
	{
		if (!(*it)->GetNeedToBeDeleted() && (*it)->GetOwner()->GetActivated())
			(*it)->LateUpdate();

		if ((*it)->GetNeedToBeDeleted())
		{
			SAFE_DELETE(*it);
			it = m_vClickableComponent.erase(it);
		}
		else
			++it;
	}
}

void CCollisionManager::Release(void)
{
}

void CCollisionManager::AddCollisionComponent(CCollisionComponent * pCC)
{
	m_vCollisionComponent[pCC->GetCollisionID()].push_back(pCC);
}

void CCollisionManager::AddClickableComponent(CClickableComponent * pCC)
{
	m_vClickableComponent.push_back(pCC);
}

CCollisionManager::CCollisionManager()
{
}


CCollisionManager::~CCollisionManager()
{
}