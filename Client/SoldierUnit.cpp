#include "stdafx.h"
#include "SoldierUnit.h"
#include "BarrackTurret.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"



CSoldierUnit::CSoldierUnit(CObject* pBarrackTurret)
{
	m_pParent = pBarrackTurret;
	
	Initialize();

	//CObject::Initialize에서 세팅해주는 것 초기화.
	m_parentPosition = D3DXVECTOR3(0, 0, 0);
}


CSoldierUnit::~CSoldierUnit()
{
}

void CSoldierUnit::Initialize(void)
{
	__super::Initialize();
	SetRallyPosition(static_cast<CBarrackTurret*>(m_pParent)->GetRallyPoint());
}

void CSoldierUnit::Update(void)
{
	__super::Update();
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();
	//스테이트키 레벨별로 분류해야함
	if(m_stateKey == "Idle")
	{
		D3DXVECTOR3 normalizedDir;
		D3DXVec3Normalize(&normalizedDir, &(m_rallyPosition - m_position));
		pPC->SetDirection(normalizedDir);
		if (D3DXVec3Length(&(m_rallyPosition - m_position)) < pPC->GetSpeed())
		{
			m_position = m_rallyPosition;
			m_stateKey = "Wait";
			StateChangeInit();
		}
	}
	else if (m_stateKey == "Wait")
	{

	}
	else if (m_stateKey == "Approach")
	{

	}
	else if (m_stateKey == "Fight")
	{

	}
	else if (m_stateKey == "Die")
	{

	}
	else if (m_stateKey == "WaitRevive")
	{

	}

}

void CSoldierUnit::LateUpdate(void)
{
	__super::LateUpdate();
}

void CSoldierUnit::Release(void)
{
}

void CSoldierUnit::UpgradeUnit(int increase)
{
	__super::UpgradeUnit();
}

void CSoldierUnit::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
	AddComponent<CPhysicsComponent>();
	AddComponent<CCollisionComponent>();
}

void CSoldierUnit::InitializeComponents(void)
{
}

void CSoldierUnit::StateChangeInit(void)
{
	__super::StateChangeInit();
}

void CSoldierUnit::Revive(void)
{
}

void CSoldierUnit::SetRallyPosition(D3DXVECTOR3 rallyPoint)
{
	float angle = D3DXToRadian(m_id * 60.f);

	m_rallyPosition = rallyPoint + D3DXVECTOR3(cosf(angle), sinf(angle), 0) * 30.f;
}

