#include "stdafx.h"
#include "TurretRing.h"
#include "Turret.h"
#include "DataStore.h"
#include "RingBox.h"
#include "InputManager.h"
#include "CollisionHelper.h"

CTurretRing::CTurretRing(CTurret* pTurret)
{
	//m_pOwner = pTurret;
	m_pParent = pTurret;
	m_activated = false;
	

	Initialize();
}


CTurretRing::~CTurretRing()
{
	Release();
}

void CTurretRing::Initialize(void)
{
	__super::Initialize();
	
	m_lastFrameActivated = false;
	m_pFocusedRingBox = nullptr;

	
	m_defaultSize = m_size;
	m_size *= 0.7f;
}

void CTurretRing::Update(void)
{
	__super::Update();

	if (m_size.x < m_defaultSize.x)
		m_size += D3DXVECTOR3((m_defaultSize * 0.3f) / 5.f);
	if(m_size.x >= m_defaultSize.x)
		m_size = m_defaultSize;

	if (!m_lastFrameActivated && m_activated)
	{
		for (auto& ringBox : m_vRingBoxes)
			ringBox->SetActivated(true);
	}


	m_lastFrameActivated = m_activated;
}

void CTurretRing::LateUpdate(void)
{
	__super::LateUpdate();
}

void CTurretRing::Release(void)
{
	for (auto& ringBox : m_vRingBoxes)
		ringBox->SetNeedToBeDeleted(true);

}

void CTurretRing::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	MakeRingBoxes();
}

void CTurretRing::InitializeComponents(void)
{
}

void CTurretRing::MakeRingBoxes(void)
{
	CTurret* pParentTurret = static_cast<CTurret*>(m_pParent);
	for (int i = 0; i < pParentTurret->GetNumOfRingBox(); ++i)
	{
		CRingBox* pRingBox = new CRingBox(this, pParentTurret->GetRingBoxInfo()[i]->name);
		pRingBox->AddChildAndComponents();
		pRingBox->SetPrice(pParentTurret->GetRingBoxInfo()[i]->price);
		pRingBox->SetAnglePosition(pParentTurret->GetRingBoxInfo()[i]->angle);

		m_vRingBoxes.push_back(pRingBox);
	}
}
