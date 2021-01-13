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
	//ID 할당
	m_objID = OBJID::TURRET;
	m_dataID = DATAID::TURRET;

	//Object에서 매니저에 등록, objectKey+stateKey 할당, 위치 크기 회전 초기화.
	__super::Initialize();

	//iniFile에서 정보 불러오기.
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_level", m_level);
	
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_sellable", m_sellable);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_sellPrice", m_sellPrice);
	
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_rallyable", m_rallyable);
	
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_numOfSkill", m_numOfSkill);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_numOfRingBox", m_numOfRingBox);

	//RingBox 심기
	for (int i = 0; i < m_numOfRingBox; ++i)
	{
		RingBoxInfo* pNewRingBoxInfo = new RingBoxInfo;

		GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_ringBox" + std::to_string(i) + "_name", pNewRingBoxInfo->name);
		GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_ringBox" + std::to_string(i) + "_price", pNewRingBoxInfo->price);
		GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_ringBox" + std::to_string(i) + "_angle", pNewRingBoxInfo->angle);

		m_vRingBoxInfo.push_back(pNewRingBoxInfo);
	}

	//터렛링 세팅
	m_pTurretRing = new CTurretRing(this);
	m_pTurretRing->SetParent(this);

	//그래픽/클릭 컴포넌트 등록
	AddComponent<CGraphicsComponent>();
	AddComponent<CClickableComponent>()->SetPlayFunc(std::bind(&CTurret::Selected, this));
}

void CTurret::Update(void)
{
	//포커싱된 오브젝트가 나라면, 내 터렛링 활성화
	if (CGameInfo::GetInstance()->GetFocusedObject() == this)
		m_pTurretRing->SetActivated(true);

	//이제 포커싱이 넘어갔다면.
	else //if(m_pTurretRing->GetLastFrameActivated() == true)
	{
		m_pTurretRing->SetSize(m_pTurretRing->GetDefaultSize() * 0.7f);
		m_pTurretRing->SetActivated(false);
		m_pTurretRing->SetLastFrameActivated(false);
		for (auto& ringBox : m_pTurretRing->GetRingBoxes())
		{
			ringBox->SetStateKey("Idle");
			ringBox->SetActivated(false);
		}
	}

	 
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
}

void CTurret::InitializeStates(void)
{
}
