#include "stdafx.h"
#include "TurretRing.h"
#include "Turret.h"
#include "DataStore.h"
#include "RingBox.h"
#include "InputManager.h"
#include "CollisionHelper.h"

CTurretRing::CTurretRing(CTurret* pTurret)
{
	m_pOwner = pTurret;
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


	for (int i = 0; i < m_pOwner->GetNumOfRingBox(); ++i)
	{
		CRingBox* pRingBox = new CRingBox(m_pOwner->GetRingBoxInfo()[i]->name);
		pRingBox->SetPrice(m_pOwner->GetRingBoxInfo()[i]->price);
		pRingBox->SetAnglePosition(m_pOwner->GetRingBoxInfo()[i]->angle);
	
		pRingBox->SetParent(this);
		pRingBox->SetTurretRing(this);
		m_vRingBoxes.push_back(pRingBox);
	}
}

void CTurretRing::Update(void)
{
	__super::Update();

	if (m_size.x < m_defaultSize.x)
		m_size += D3DXVECTOR3((m_defaultSize - m_defaultSize * 0.7f) / 5.f);
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

}

void CTurretRing::Release(void)
{
	for (auto& ringBox : m_vRingBoxes)
		ringBox->SetNeedToBeDeleted(true);

}
