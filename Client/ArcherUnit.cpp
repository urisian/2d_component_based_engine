#include "stdafx.h"
#include "ArcherUnit.h"
#include "ArcherTurret.h"
#include "ArrowProjectile.h"
#include "GraphicsComponent.h"
#include "Effect.h"
#include "DataStore.h"

CArcherUnit::CArcherUnit(CObject* pArcherTurret)
{
	m_pParent = pArcherTurret;
	Initialize();
}


CArcherUnit::~CArcherUnit()
{
}

void CArcherUnit::Initialize(void)
{
	__super::Initialize();

}

void CArcherUnit::Update(void)
{
	__super::Update();

	CArcherTurret* pAT = static_cast<CArcherTurret*>(m_pParent);
	CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();

	std::string saveKey = m_stateKey;
	if (m_pTarget == nullptr)
	{
		m_stateKey = "Lv" + std::to_string(m_level) + "_Right";
		pGC->SetXFlip(false);
	}
	else
	{
		D3DXVECTOR3 attackDir = m_pTarget->GetFinalPos() - (m_position + m_parentPosition);

		if (attackDir.x < 0)
			pGC->SetXFlip(true);
		else
			pGC->SetXFlip(false);

		if (pAT->GetArchers()[pAT->GetShootTurn() % 2] == this)
		{
			if (attackDir.y < 0)
				m_stateKey = "Lv" + std::to_string(m_level) + "_RightAttack";
			else
				m_stateKey = "Lv" + std::to_string(m_level) + "_BackRightAttack";
		}
		else
		{
			if (attackDir.y < 0)
				m_stateKey = "Lv" + std::to_string(m_level) + "_Right";
			else
				m_stateKey = "Lv" + std::to_string(m_level) + "_Back";
		}

		if (m_pTarget->GetStateKey() == "Die")
			m_pTarget = nullptr;
	}

	if(saveKey != m_stateKey)
		StateChangeInit();

	if(m_pTarget != nullptr)
		Shoot();
}

void CArcherUnit::LateUpdate(void)
{
	__super::LateUpdate();
}

void CArcherUnit::Release(void)
{
}

void CArcherUnit::UpgradeUnit(int increase)
{
	m_level += increase;
	m_stateKey = "Lv" + std::to_string(m_level) + "_Right";

	__super::UpgradeUnit(increase);
}

void CArcherUnit::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
}

void CArcherUnit::InitializeComponents(void)
{
}

void CArcherUnit::StateChangeInit(void)
{
	__super::StateChangeInit();
}

void CArcherUnit::Shoot(void)
{
	if (m_attackTimer >= m_attackSpeed)
	{
		CArrowProjectile* pAP = new CArrowProjectile(this);
		pAP->AddChildAndComponents();

		static_cast<CArcherTurret*>(m_pParent)->GetShootTurn() += 1;

		m_attackTimer = 0.f;
		if (m_level == 4)
		{
			CEffect* pEffect = new CEffect("Fire", "Idle", this, 0, false);
			pEffect->AddChildAndComponents();

			D3DXVECTOR3 direction = m_pTarget->GetFinalPos() - GetFinalPos();

			D3DXVec3Normalize(&direction, &direction);
			pEffect->SetRotation(GetAngleFromDir(direction));
			pEffect->SetPosition(pEffect->GetPosition() + direction * 30);
		}
	}
}

