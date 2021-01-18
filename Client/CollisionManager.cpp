#include "stdafx.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "CollisionComponent.h"
#include "ClickableComponent.h"
#include "GameInfo.h"
#include "Monster.h"

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

	for (auto& it = m_vClickableComponent.begin(); it != m_vClickableComponent.end(); )
	{
		if ((*it)->GetActivated() && !(*it)->GetNeedToBeDeleted())
			(*it)->Update();

		if ((*it)->GetNeedToBeDeleted())
		{
			SAFE_DELETE(*it);
			it = m_vClickableComponent.erase(it);
		}
		else
			++it;
	}

	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& it = m_vCollisionComponent[i].begin(); it != m_vCollisionComponent[i].end(); )
		{
			if ((*it)->GetActivated() && !(*it)->GetNeedToBeDeleted())
				(*it)->Update();

			if ((*it)->GetNeedToBeDeleted())
			{
				SAFE_DELETE(*it);
				it = m_vCollisionComponent[i].erase(it);
			}
			else
				++it;
		}
	}
}

void CCollisionManager::LateUpdate(void)
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
			m_vClickableComponent[i]->CheckMouseOver();
			m_vClickableComponent[i]->CheckClickUp();
			m_vClickableComponent[i]->CheckClickDown();

			if (m_vClickableComponent[i]->GetClickUp())
			{
				anyClick = true;
				break;
			}
		}
	}

	for (int i = 0; i < OBJID::END; ++i)
	{
		if (i == OBJID::MONSTER)
			std::sort(m_vCollisionComponent[i].begin(),
				m_vCollisionComponent[i].end(),
				[](CCollisionComponent* pCC1, CCollisionComponent* pCC2)
		{
			return static_cast<CMonster*>(pCC1->GetOwner())->GetRouteDistance() < static_cast<CMonster*>(pCC2->GetOwner())->GetRouteDistance();
		});


		for (unsigned int j = 0; j < m_vCollisionComponent[i].size(); ++j)
		{
			if (!m_vCollisionComponent[i][j]->GetNeedToBeDeleted() && m_vCollisionComponent[i][j]->GetOwner()->GetActivated())
				m_vCollisionComponent[i][j]->Update();
		}
	}


	if (IMKEY_UP(MOUSE_LEFT) && !anyClick)
		CGameInfo::GetInstance()->SetFocusedObject(nullptr);
}

void CCollisionManager::Release(void)
{
	for (auto& clickableComponent : m_vClickableComponent)
		SafeDelete(clickableComponent);

	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& collisionComponent : m_vCollisionComponent[i])
			SafeDelete(collisionComponent);
	}

}

void CCollisionManager::AddCollisionComponent(CCollisionComponent * pCC)
{
	m_vCollisionComponent[pCC->GetOwner()->GetObjID()].push_back(pCC);
}

void CCollisionManager::AddClickableComponent(CClickableComponent * pCC)
{
	m_vClickableComponent.push_back(pCC);
}

std::vector<CCollisionComponent*> CCollisionManager::GetCollisionVector(OBJID::ID objID)
{
	return m_vCollisionComponent[objID];
}

CCollisionManager::CCollisionManager()
{
}


CCollisionManager::~CCollisionManager()
{
	Release();
}