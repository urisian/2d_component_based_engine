#include "stdafx.h"
#include "BombTurret.h"
#include "FRC.h"
#include "DataStore.h"
#include "GraphicsComponent.h"
#include "Animation.h"
#include "BombProjectile.h"

CBombTurret::CBombTurret()
{
	Initialize();
	m_attackFrameNum = 0;
}


CBombTurret::~CBombTurret()
{
	Release();
}

void CBombTurret::Initialize(void)
{
	__super::Initialize();
	m_attackTimer = m_attackCooltime;

	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_attackFrameNum", m_attackFrameNum);
}

void CBombTurret::Update(void)
{
	__super::Update();
	if (m_pTarget != nullptr)
	{
		if (m_attackTimer >= m_attackCooltime)
		{
			m_stateKey = "Lv" + std::to_string(m_level) + "_Fire";
			StateChangeInit();
			m_attackTimer = 0.f;
		}

		if (m_stateKey.find("Fire") != std::string::npos)
		{
			CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();

			if ((int)pGC->GetAnimation()->GetCurIndex() == m_attackFrameNum &&
				(int)pGC->GetAnimation()->GetCurIndex() != pGC->GetAnimation()->GetLastFrameIndex())
			{
				CBombProjectile* pBP = new CBombProjectile(this);
				pBP->AddChildAndComponents();
			}
			else if ((int)pGC->GetAnimation()->GetCurIndex() == 0 &&
					 (int)pGC->GetAnimation()->GetCurIndex() != pGC->GetAnimation()->GetLastFrameIndex())
			{
				m_stateKey = "Lv" + std::to_string(m_level) + "_Idle";
				StateChangeInit();
			}

		}
	}
	else
	{
		m_stateKey = "Lv" + std::to_string(m_level) + "_Idle";
		StateChangeInit();
	}

	m_attackTimer += GET_DT();
}

void CBombTurret::LateUpdate(void)
{
	__super::LateUpdate();
}

void CBombTurret::Release(void)
{
}

void CBombTurret::UpgradeTurret(int increase)
{
	__super::UpgradeTurret(increase);
	GET_VALUE(m_dataID, m_objectKey, m_basicStateKey + "_m_attackFrameNum", m_attackFrameNum);
}

void CBombTurret::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
}

void CBombTurret::InitializeComponents(void)
{
}
