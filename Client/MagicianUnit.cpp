#include "stdafx.h"
#include "MagicianUnit.h"
#include "MagicTurret.h"
#include "GraphicsComponent.h"
#include "MagicBallProjectile.h"
#include "DataStore.h"

CMagicianUnit::CMagicianUnit(CObject* pMagicTurret)
{
	m_pParent = pMagicTurret;
	Initialize();
}


CMagicianUnit::~CMagicianUnit()
{
}

void CMagicianUnit::Initialize(void)
{
	__super::Initialize();
}

void CMagicianUnit::Update(void)
{
	__super::Update();
	CMagicTurret* pMT = static_cast<CMagicTurret*>(m_pParent);
	CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();

	std::string saveKey = m_stateKey;

	if (m_pTarget == nullptr)
	{
		m_stateKey = "Lv" + std::to_string(m_level) + "_Front";
		pGC->SetXFlip(false);
	}
	else
	{
		D3DXVECTOR3 attackDir = m_pTarget->GetFinalPos() - (m_position + m_parentPosition);

		if (attackDir.x < 0)
			pGC->SetXFlip(true);
		else
			pGC->SetXFlip(false);

		if (attackDir.y < 0)
			m_stateKey = "Lv" + std::to_string(m_level) + "_FrontAttack";
		else
			m_stateKey = "Lv" + std::to_string(m_level) + "_BackAttack";

		if (m_pTarget->GetStateKey() == "Die")
			m_pTarget = nullptr;
	}

	if (saveKey != m_stateKey)
		StateChangeInit();

	if (m_pTarget != nullptr)
		Shoot();
}

void CMagicianUnit::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMagicianUnit::Release(void)
{
}

void CMagicianUnit::UpgradeUnit(int increase)
{
	m_level += increase;
	m_stateKey = "Lv" + std::to_string(m_level) + "_Front";

	__super::UpgradeUnit(increase);
}

void CMagicianUnit::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
}

void CMagicianUnit::InitializeComponents(void)
{
}

void CMagicianUnit::StateChangeInit(void)
{
	__super::StateChangeInit();
}

void CMagicianUnit::Shoot(void)
{
	if (m_attackTimer >= m_attackSpeed)
	{
		CMagicBallProjectile* pMBP = new CMagicBallProjectile(this);
		pMBP->AddChildAndComponents();

		m_attackTimer = 0.f;
		
		//레벨4일때?
	}
}
