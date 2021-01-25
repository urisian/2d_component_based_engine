#include "stdafx.h"
#include "Turret.h"
#include "DataStore.h"
#include "ObjectManager.h"
#include "TurretRing.h"
#include "RingBox.h"
#include "GameInfo.h"
#include "BaseTurret.h"
#include "Decoration.h"
#include "CollisionManager.h"
#include "CollisionHelper.h"
#include "CollisionComponent.h"
#include "ClickableComponent.h"
#include "GraphicsComponent.h"

CTurret::CTurret()
{
	m_pTarget = nullptr;
}


CTurret::~CTurret()
{
	Release();
}

void CTurret::Initialize(void)
{
	//ID �Ҵ�
	m_objID = OBJID::TURRET;
	m_dataID = DATAID::TURRET;

	//Object���� �Ŵ����� ���, objectKey+stateKey �Ҵ�, ��ġ ũ�� ȸ�� �ʱ�ȭ.
	__super::Initialize();
	
	CTurret::ReadDataFromStore();

}

void CTurret::Update(void)
{
	__super::Update();


	//��Ŀ�̵� ������Ʈ�� �����, �� �ͷ��� Ȱ��ȭ
	if (CGameInfo::GetInstance()->GetFocusedObject() == this)
	{
		m_pRangeCircle->SetActivated(true);
		m_pTurretRing->SetActivated(true);
	}
	//���� ��Ŀ���� �Ѿ�ٸ�.
	else //if(m_pTurretRing->GetLastFrameActivated() == true)
	{
		m_pRangeCircle->SetActivated(false);

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
	__super::LateUpdate();
	FindTarget();
}

void CTurret::Release(void)
{
	for (auto& element : m_vRingBoxInfo)
	{
		SAFE_DELETE(element);
	}

	m_vRingBoxInfo.clear();
	
	m_pRangeCircle->SetNeedToBeDeleted(true);
	m_pTurretRing->SetNeedToBeDeleted(true);
}

void CTurret::UpgradeTurret(int increase)
{
	CTurret::Release();

	m_level += increase;
	m_stateKey.replace(2, 1, std::to_string(m_level));
	m_basicStateKey.replace(2, 1, std::to_string(m_level));
	

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_position", m_position);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_rotation", m_rotation);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_size", m_size);

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_numOfSkill", m_numOfSkill);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_numOfRingBox", m_numOfRingBox);

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_sellable", m_sellable);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_sellPrice", m_sellPrice);

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_rallyable", m_rallyable);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_rallyRange", m_rallyRange);

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_attackRange", m_attackRange);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_attackCooltime", m_attackCooltime);

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_dmg", m_dmg);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_magicDmg", m_magicDmg);

	m_attackTimer = 0;

	MakeRingBoxInfo();

	//RangedCircle ����
	MakeRangeCircle();

	//�ͷ��� ����
	MakeTurretRing();

	StateChangeInit();
}

void CTurret::SellTurret(void)
{
	CGameInfo::GetInstance()->SetGold(CGameInfo::GetInstance()->GetGold() + m_sellPrice);

	m_needToBeDeleted = true;

	CBaseTurret* pNewTurret = new CBaseTurret;
	pNewTurret->SetPosition(m_parentPosition);
	pNewTurret->AddChildAndComponents();
}

void CTurret::AddChildAndComponents(void)
{
	MakeRingBoxInfo();
	MakeTurretRing();
	MakeRangeCircle();

	//�׷���/Ŭ�� ������Ʈ ���
	AddComponent<CCollisionComponent>();
	AddComponent<CGraphicsComponent>();
	AddComponent<CClickableComponent>()->SetPlayFunc(std::bind(&CTurret::Selected, this));
}



void CTurret::ReadDataFromStore(void)
{
	//iniFile���� ���� �ҷ�����.
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_level", m_level);

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_numOfSkill", m_numOfSkill);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_numOfRingBox", m_numOfRingBox);

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_sellable", m_sellable);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_sellPrice", m_sellPrice);

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_rallyable", m_rallyable);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_rallyRange", m_rallyRange);

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_attackRange", m_attackRange);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_attackCooltime", m_attackCooltime);

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_dmg", m_dmg);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_magicDmg", m_magicDmg);
}

void CTurret::MakeRingBoxInfo(void)
{
	//RingBoxInfo �ɱ�
	for (int i = 0; i < m_numOfRingBox; ++i)
	{
		RingBoxInfo* pNewRingBoxInfo = new RingBoxInfo;

		GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_ringBox" + std::to_string(i) + "_name", pNewRingBoxInfo->name);
		GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_ringBox" + std::to_string(i) + "_price", pNewRingBoxInfo->price);
		GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_ringBox" + std::to_string(i) + "_angle", pNewRingBoxInfo->angle);

		m_vRingBoxInfo.push_back(pNewRingBoxInfo);
	}
}

void CTurret::MakeTurretRing(void)
{
	//�ͷ��� ����
	m_pTurretRing = new CTurretRing(this);
	m_pTurretRing->AddChildAndComponents();
}

void CTurret::MakeRangeCircle(void)
{
	//RangeCircle �ɱ�
	m_pRangeCircle = new CDecoration("RangeCircle", "Green", this);
	m_pRangeCircle->AddChildAndComponents();
	m_pRangeCircle->SetSize(D3DXVECTOR3(m_attackRange, m_attackRange * 0.6f, 0));
}

void CTurret::Selected(void)
{
	CGameInfo::GetInstance()->SetFocusedObject(this);
}

void CTurret::FindTarget(void)
{
	m_pTarget = nullptr;

	if (m_attackRange > 0)
	{
		for (auto& monsterCC : CCollisionManager::GetInstance()->GetCollisionVector(OBJID::MONSTER))
		{
			if (monsterCC->GetOwner()->GetStateKey() != "Die")
			{
				if (CollisionHelper::PointEclipseCollision(monsterCC->GetPosition(),
														   m_position + m_parentPosition,
														   m_pRangeCircle->GetSize()))
				{
					m_pRangeCircle->SetStateKey("Blue");
					m_pRangeCircle->StateChangeInit();
					m_pTarget = monsterCC->GetOwner();
					break;
				}
			}
		}
	}


	if (m_pTarget == nullptr && m_pRangeCircle->GetStateKey() != "Green")
	{
		m_pRangeCircle->SetStateKey("Green");
		m_pRangeCircle->StateChangeInit();
	}
}

