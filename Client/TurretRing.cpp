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
	Initialize();
}


CTurretRing::~CTurretRing()
{
}

void CTurretRing::Initialize(void)
{
	__super::Initialize();
	
	m_activated = false;


	
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
	else
		m_size = m_defaultSize;



	//bool clickedRingBox = false;
	//if (IMKEY_UP(MOUSE_LEFT) && !CollisionHelper::PointRectCollision(GET_MOUSE_POS(), this))
	//{
	//	for (int i = 0; i < m_pOwner->GetNumOfRingBox(); ++i)
	//	{
	//		if (CollisionHelper::PointRectCollision(GET_MOUSE_POS(), m_vRingBoxes[i]))
	//		{
	//			clickedRingBox = true;
	//		}
	//	}
	//}
	//
	//if (clickedRingBox == false)
	//{
	//	m_activated = false;
	//	for (int i = 0; i < m_pOwner->GetNumOfRingBox(); ++i)
	//	{
	//		m_vRingBoxes[i]->SetActivated(false);
	//	}
	//}
}

void CTurretRing::LateUpdate(void)
{

}

void CTurretRing::Release(void)
{
}
