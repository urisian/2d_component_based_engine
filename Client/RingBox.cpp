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
	__super::Initialize();

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

