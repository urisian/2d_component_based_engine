#include "stdafx.h"
#include "Object.h"
#include "ObjectManager.h"
#include "DataStore.h"
#include "Component.h"
#include "GSM.h"
#include "GameState.h"

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

void CObject::Initialize(void)
{
	CObjectManager::GetInstance()->AddObject(this, m_objID);

	if(m_objectKey == "")
		m_objectKey = GetCurClassName(this);

	CObject::ReadDataFromStore();
}

void CObject::Update(void)
{
	if (m_pParent)
		m_parentPosition = m_pParent->GetParentPosition() + m_pParent->GetPosition();
}

void CObject::Release(void)
{
	for (auto& component : m_mComponents)
		component.second->SetNeedToBeDeleted(true);
}

void CObject::StateChangeInit(void)
{
	for (auto& component : m_mComponents)
		component.second->StateChangeInit();

}

void CObject::ReadDataFromStore(void)
{
	if (m_stateKey == "")
		GET_VALUE(m_dataID, m_objectKey, "m_stateKey", m_stateKey);

	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_position", m_position);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_rotation", m_rotation);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_size", m_size);
}
