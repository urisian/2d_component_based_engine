#include "stdafx.h"
#include "Turret.h"
#include "DataStore.h"
#include "GraphicsComponent.h"
#include "ObjectManager.h"
#include "ClickableComponent.h"
#include "TurretRing.h"
#include "RingBox.h"
#include "GameInfo.h"

CTurret::CTurret()
{
}


CTurret::~CTurret()
{
	Release();
}

void CTurret::Initialize(void)
{
	m_objID = OBJID::TURRET;
	m_dataID = DATAID::TURRET;

	__super::Initialize();

	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_level", m_level);
	
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_sellable", m_sellable);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_sellPrice", m_sellPrice);
	
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_rallyable", m_rallyable);
	
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_numOfSkill", m_numOfSkill);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_numOfRingBox", m_numOfRingBox);

	for (int i = 0; i < m_numOfRingBox; ++i)
	{
		RingBoxInfo* pNewRingBoxInfo = new RingBoxInfo;

		GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_ringBox" + std::to_string(i) + "_name", pNewRingBoxInfo->name);
		GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_ringBox" + std::to_string(i) + "_price", pNewRingBoxInfo->price);
		GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_ringBox" + std::to_string(i) + "_angle", pNewRingBoxInfo->angle);

		m_vRingBoxInfo.push_back(pNewRingBoxInfo);
	}

	m_pTurretRing = new CTurretRing(this);
	m_pTurretRing->SetParent(this);

	AddComponent<CGraphicsComponent>();
	AddComponent<CClickableComponent>()->SetPlayFunc(std::bind(&CTurret::Selected, this));
}

void CTurret::Update(void)
{
	GetComponent<CGraphicsComponent>()->Update();
	GetComponent<CClickableComponent>()->Update();
}

void CTurret::LateUpdate(void)
{
}

void CTurret::Release(void)
{
	for (auto& element : m_vRingBoxInfo)
	{
		SAFE_DELETE(element);
	}
}

void CTurret::Selected(void)
{
	CGameInfo::GetInstance()->SetFocusedObject(this);
	m_pTurretRing->SetActivated(true);
	for (auto& ringBox : m_pTurretRing->GetRingBoxes())
		ringBox->SetActivated(true);

}
