#include "stdafx.h"
#include "OrgeMonster.h"
#include "PhysicsComponent.h"
#include "Debugger.h"
#include "FRC.h"
#include "Effect.h"
#include "GraphicsComponent.h"
#include "Animation.h"
#include "FadeOutEffectComponent.h"
#include "Unit.h"


COrgeMonster::COrgeMonster()
{
	Initialize();
}


COrgeMonster::~COrgeMonster()
{
	Release();
}

void COrgeMonster::Initialize(void)
{
	__super::Initialize();
}

void COrgeMonster::Update(void)
{
	__super::Update();

	std::string saveState = m_stateKey;
	CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();
	CUnit* pUnit = static_cast<CUnit*>(m_pTarget);
	if (m_stateKey != "Die")
	{
		if (m_pTarget != nullptr)
		{
			if ((D3DXVec3Length(&(m_position - m_pTarget->GetFinalPos())) <= m_size.x / 2.f + m_pTarget->GetSize().x / 2.f) &&
				m_position.y == m_pTarget->GetFinalPos().y)
			{
				m_stateKey = "Attack";
				if ((int)pGC->GetAnimation()->GetCurIndex() == m_attackFrameNum &&
					(int)pGC->GetAnimation()->GetCurIndex() != pGC->GetAnimation()->GetLastFrameIndex())
				{
					float actualDmg = (1 - pUnit->GetArmor()) * m_dmg;
					float actualMagicDmg = (1 - pUnit->GetMR()) * m_magicDmg;

					pUnit->GetHP() -= (actualDmg + actualMagicDmg);
					CEffect* pEffect = new CEffect("BloodDrop", "Idle", m_pTarget, 0, false);
					pEffect->AddChildAndComponents();
				}
			}
			else
				m_stateKey = "Idle";

			GetComponent<CGraphicsComponent>()->SetXFlip(true);
		}
		else
		{
			if (m_routeIndex < m_pRouteInfo->routePoints.size())
			{

				m_stateKey = "Walk";
				if (m_direction.y < 0 && (abs(m_direction.y) > abs(m_direction.x)))
					m_stateKey += "Down";
				else if (m_direction.y > 0 && (abs(m_direction.y) > abs(m_direction.x)))
					m_stateKey += "Up";
				else
				{
					m_stateKey += "Hor";
					if (m_direction.x < 0)
						GetComponent<CGraphicsComponent>()->SetXFlip(true);
					else if (m_direction.x > 0)
						GetComponent<CGraphicsComponent>()->SetXFlip(false);
				}

				m_routeDistance -= GetComponent<CPhysicsComponent>()->GetSpeed() * GET_DT();
			}
			else
				m_stateKey = "Idle";
		}
	}

	if (saveState != m_stateKey)
		StateChangeInit();
}

void COrgeMonster::LateUpdate(void)
{
	__super::LateUpdate();
}

void COrgeMonster::Release(void)
{
}

void COrgeMonster::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
}

void COrgeMonster::InitializeComponents(void)
{
}

void COrgeMonster::Die(void)
{
	if (m_stateKey != "Die")
	{
		__super::Die();
		CEffect* pEffect = new CEffect("BloodPond", "Idle", this, -1, true);
		pEffect->AddChildAndComponents();
		pEffect->AddComponent<CFadeOutEffectComponent>();

		m_stateKey = "Die";
		StateChangeInit();
		GetComponent<CGraphicsComponent>()->GetAnimation()->SetRepeat(false);
	}
}


