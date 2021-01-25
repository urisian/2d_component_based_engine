#include "stdafx.h"
#include "Object.h"
#include "ObjectManager.h"
#include "DataStore.h"
#include "Component.h"
#include "GSM.h"
#include "GameState.h"
#include "GraphicsComponent.h"

CObject::CObject()
{
	m_objID				= {};
	m_dataID			= {};

	m_objectKey			= "";
	m_stateKey			= "";

	m_activated			= true;
	m_needToBeDeleted	= false;

	m_parentPosition	= D3DXVECTOR3(0, 0, 0);
	m_position			= D3DXVECTOR3(0, 0, 0);
	m_direction			= D3DXVECTOR3(1, 0, 0);
	m_rotation			= D3DXVECTOR3(0, 0, 0);
	m_size				= D3DXVECTOR3(1, 1, 0);

	m_pParent			= nullptr;
}


CObject::~CObject()
{
	Release();
}

//모든 오브젝트는 만들어질 때 Constructor 이후에 여기로 온다.
void CObject::Initialize(void)
{
	//오브젝트 리스트에 추가.
	CObjectManager::GetInstance()->AddObject(this, m_objID);

	//부모가 있다면 부모 좌표 설정
	if (m_pParent)
		m_parentPosition = m_pParent->GetParentPosition() + m_pParent->GetPosition();

	//오브젝트 키가 없는 경우 설정
	if(m_objectKey == "")
		m_objectKey = GetCurClassName(this);


	//오브젝트 기본 정보 세팅
	CObject::ReadDataFromStore();
}

void CObject::Update(void)
{
	for (auto& it = m_mComponents.begin(); it != m_mComponents.end();)
	{
		(*it).second->Update();
		if ((*it).second->GetNeedToBeDeleted() == true)
		{
			delete (*it).second;
			it = m_mComponents.erase(it);
		}
		else
			++it;
	}
}

void CObject::LateUpdate(void)
{
	for (auto& component : m_mComponents)
		component.second->LateUpdate();
}

void CObject::Release(void)
{
	for (auto& component : m_mComponents)
		component.second->SetNeedToBeDeleted(true);
}

void CObject::EraseElementFromMap(std::string objectKey)
{
	m_mComponents.erase(objectKey);
}

void CObject::StateChangeInit(void)
{
	for (auto& component : m_mComponents)
		component.second->StateChangeInit();

}

D3DXVECTOR3 CObject::GetFinalPos(void)
{
	return m_parentPosition + m_position;
}

void CObject::ReadDataFromStore(void)
{
	if (m_stateKey == "")
		GET_VALUE(m_dataID, m_objectKey, "m_stateKey", m_stateKey);

	m_basicStateKey = m_stateKey;

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_position", m_position);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_rotation", m_rotation);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_size", m_size);
}
