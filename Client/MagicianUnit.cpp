#include "stdafx.h"
#include "MagicianUnit.h"
#include "MagicTurret.h"
#include "GraphicsComponent.h"
#include "MagicBallProjectile.h"
#include "DataStore.h"
#include "Animation.h"

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
		D3DXVECTOR3 attackDir = m_pTarget->GetFinalPos() - m_pParent->GetFinalPos();

		if (attackDir.x < 0)
			pGC->SetXFlip(true);
		else
			pGC->SetXFlip(false);

		if (m_attackNow)
		{
			if (attackDir.y < 0)
				m_stateKey = "Lv" + std::to_string(m_level) + "_FrontAttack";
			else
				m_stateKey = "Lv" + std::to_string(m_level) + "_BackAttack";
		}
		else
		{
			if (attackDir.y < 0)
				m_stateKey = "Lv" + std::to_string(m_level) + "_Front";
			else
				m_stateKey = "Lv" + std::to_string(m_level) + "_Back";
		}
	}

	if (saveKey != m_stateKey)
		StateChangeInit();

	if (m_attackNow && (int)pGC->GetAnimation()->GetCurIndex() == m_attackFrameNum)
	{
		if ((int)pGC->GetAnimation()->GetCurIndex() != pGC->GetAnimation()->GetLastFrameIndex())
			Shoot();
	}
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
	CMagicBallProjectile* pMBP = new CMagicBallProjectile(this);
	pMBP->AddChildAndComponents();

	m_attackNow = false;

	//레벨4일때?

}
