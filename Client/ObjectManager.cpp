#include "stdafx.h"
#include "ObjectManager.h"
#include "Object.h"

CObjectManager* CObjectManager::m_s_pInstance = nullptr;



CObjectManager * CObjectManager::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CObjectManager;

	return m_s_pInstance;
}

void CObjectManager::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CObjectManager::Initialize(void)
{
}

void CObjectManager::Update(void)
{

	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& it = m_vObjects[i].begin(); it != m_vObjects[i].end(); )
		{
			if ((*it)->GetActivated() && !(*it)->GetNeedToBeDeleted())
				(*it)->Update();

			if ((*it)->GetNeedToBeDeleted())
			{
				SAFE_DELETE(*it);
				it = m_vObjects[i].erase(it);
			}
			else
				++it;
		}
	}
}

void CObjectManager::LateUpdate(void)
{
	
	for (int i = 0; i < OBJID::END; ++i)
	{
		int vectorSize = m_vObjects[i].size();
		for (int j = 0; j < vectorSize; ++j)
		{
			if (m_vObjects[i][j]->GetActivated() && !m_vObjects[i][j]->GetNeedToBeDeleted())
				m_vObjects[i][j]->LateUpdate();
		}
	}
}

void CObjectManager::Release(void)
{
	for (int i = 0; i < OBJID::END; ++i)
		for (auto& object : m_vObjects[i])
			SafeDelete(object);
}

void CObjectManager::AddObject(CObject * pObj, OBJID::ID objID)
{
	m_vObjects[objID].emplace_back(pObj);
}

std::vector<CObject*>(&CObjectManager::GetObjectList(void))[OBJID::END]
{
	return m_vObjects;
}

CObjectManager::CObjectManager(void)
{
}


CObjectManager::~CObjectManager(void)
{
	Release();
}