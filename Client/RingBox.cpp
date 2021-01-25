#include "stdafx.h"
#include "RingBox.h"
#include "TurretRing.h"
#include "ObjectManager.h"
#include "DataStore.h"
#include "GraphicsComponent.h"
#include "ClickableComponent.h"
#include "PhysicsComponent.h"
#include "GameInfo.h"
#include "Turret.h"
#include "ArcherTurret.h"
#include "MagicTurret.h"
#include "BombTurret.h"
#include "BarrackTurret.h"
#include "Decoration.h"

CRingBox::CRingBox(CTurretRing* pParent, std::string objectKey)
{
	m_pParent = pParent;
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

}

void CRingBox::Update(void)
{
	__super::Update();

	CTurretRing* pTurretRing = static_cast<CTurretRing*>(m_pParent);
	SetPosition(D3DXVECTOR3(cosf(D3DXToRadian(m_anglePosition)), sinf(D3DXToRadian(m_anglePosition)), 0) * pTurretRing->GetSize().x / 2.f);

	if (pTurretRing->GetFocusedRingBox() != this)
		m_stateKey = "Idle";
}

void CRingBox::LateUpdate(void)
{
	__super::LateUpdate();
}

void CRingBox::Release(void)
{
}

void CRingBox::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	AddComponent<CClickableComponent>()->SetPlayFunc(std::bind(&CRingBox::Selected, this));
}

void CRingBox::InitializeComponents(void)
{
}

void CRingBox::Selected(void)
{
	CTurretRing* pTurretRing = static_cast<CTurretRing*>(m_pParent);
	pTurretRing->SetFocusedRingBox(this);

	if (m_stateKey == "Idle")
		m_stateKey = "Selected";
	else if (m_stateKey == "Selected")
	{
		CTurret* pTurretRingParent = static_cast<CTurret*>(pTurretRing->GetParent());

		if (CGameInfo::GetInstance()->GetFocusedObject()->GetObjectKey() == "BaseTurret")
		{
			CTurret* pTurret = nullptr;

			if (m_objectKey == "Archer_RingBox")
				pTurret = new CArcherTurret;
			else if (m_objectKey == "Barrack_RingBox")
				pTurret = new CBarrackTurret;
			else if (m_objectKey == "Magic_RingBox")
				pTurret = new CMagicTurret;
			else if (m_objectKey == "Bomb_RingBox")
				pTurret = new CBombTurret;

			pTurret->SetParentPosition(pTurretRingParent->GetPosition());
			pTurret->AddChildAndComponents();

			pTurretRingParent->SetNeedToBeDeleted(true);
		}
		else if (m_objectKey == "Upgrade_RingBox")
			pTurretRingParent->UpgradeTurret();
		else if (m_objectKey == "Sell_RingBox")
			pTurretRingParent->SellTurret();
		else if (m_objectKey == "Rally_RingBox")
		{
			CBarrackTurret* pBT = static_cast<CBarrackTurret*>(pTurretRing->GetParent());
			pBT->GetRallyCircle()->SetActivated(true);
		}
		else if (pTurretRingParent->GetLevel() == 2)
		{
			if (m_anglePosition == 135)
				pTurretRingParent->UpgradeTurret();
			else if (m_anglePosition == 45)
				pTurretRingParent->UpgradeTurret(2);
		}

		CGameInfo::GetInstance()->SetFocusedObject(nullptr);
	}
}

