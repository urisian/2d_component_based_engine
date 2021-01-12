#include "stdafx.h"
#include "RingBox.h"
#include "TurretRing.h"
#include "ObjectManager.h"
#include "DataStore.h"
#include "GraphicsComponent.h"
#include "ClickableComponent.h"
#include "PhysicsComponent.h"

CRingBox::CRingBox(std::string objectKey)
{
	m_objectKey = objectKey;
	m_activated = false;
	Initialize();
}


CRingBox::~CRingBox()
{
}

void CRingBox::Initialize(void)
{
	//링박스는 예외적으로 따로 이니셜라이즈 함. 상속받는 대신.
	PreInitialize();

	AddComponent<CClickableComponent>();
}

void CRingBox::Update(void)
{
	__super::Update();
	D3DXVECTOR3 a = D3DXVECTOR3(cosf(D3DXToRadian(m_anglePosition)), sinf(D3DXToRadian(m_anglePosition)), 0);
	float b = m_pTurretRing->GetSize().x;
	SetPosition(D3DXVECTOR3(cosf(D3DXToRadian(m_anglePosition)), sinf(D3DXToRadian(m_anglePosition)), 0) * m_pTurretRing->GetSize().x / 2.f);
}

void CRingBox::LateUpdate(void)
{
}

void CRingBox::Release(void)
{
}

void CRingBox::PreInitialize(void)
{
	m_objID = OBJID::UI;
	m_dataID = DATAID::UI;

	CObjectManager::GetInstance()->AddObject(this, m_objID);

	GET_VALUE(m_dataID, m_objectKey, "m_stateKey", m_stateKey);

	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_position", m_position);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_rotation", m_rotation);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_size", m_size);

	AddComponent<CGraphicsComponent>();
}
