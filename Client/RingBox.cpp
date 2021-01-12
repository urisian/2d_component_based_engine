#include "stdafx.h"
#include "RingBox.h"
#include "TurretRing.h"
#include "ObjectManager.h"
#include "DataStore.h"
#include "GraphicsComponent.h"
#include "ClickableComponent.h"
#include "PhysicsComponent.h"
#include "GameInfo.h"

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

	GET_VALUE(m_dataID, m_objectKey, "m_type", m_type);

	AddComponent<CClickableComponent>()->SetPlayFunc(std::bind(&CRingBox::Selected, this));
}

void CRingBox::Update(void)
{
	__super::Update();

	SetPosition(D3DXVECTOR3(cosf(D3DXToRadian(m_anglePosition)), sinf(D3DXToRadian(m_anglePosition)), 0) * m_pTurretRing->GetSize().x / 2.f);

	if (m_pTurretRing->GetFocusedRingBox() != this)
		m_stateKey = "Idle";
}

void CRingBox::LateUpdate(void)
{
}

void CRingBox::Release(void)
{
}

void CRingBox::Selected(void)
{
	m_pTurretRing->SetFocusedRingBox(this);

	if (m_stateKey == "Idle")
		m_stateKey = "Selected";
	else if (m_stateKey == "Selected")
	{
		if (CGameInfo::GetInstance()->GetFocusedObject()->GetObjectKey() == "BaseTurret")
		{
			if (m_objectKey == "Archer_RingBox")
				;
			else if (m_objectKey == "Barrack_RingBox")
				;
			else if (m_objectKey == "Magic_RingBox")
				;
			else if (m_objectKey == "Bomb_RingBox")
				;
		}
		else if (m_objectKey == "Upgrade_RingBox")
			;
		else if (m_objectKey == "Sell_RingBox")
			;
		else if (m_objectKey == "Rally_RingBox")
			;
		else if (m_objectKey == "Repair_RingBox")
			;


	}
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

