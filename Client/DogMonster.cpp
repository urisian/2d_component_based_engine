#include "stdafx.h"
#include "DogMonster.h"
#include "PhysicsComponent.h"
#include "Debugger.h"
#include "FRC.h"
#include "Effect.h"
#include "GraphicsComponent.h"
#include "Animation.h"
#include "FadeOutEffectComponent.h"
#include "Unit.h"

CDogMonster::CDogMonster()
{
	Initialize();
}


CDogMonster::~CDogMonster()
{
	Release();
}

void CDogMonster::Initialize(void)
{
	__super::Initialize();
	m_skilltimer = 10;
	m_skillCooltime = 10;
}

void CDogMonster::Update(void)
{
	__super::Update();

	std::string saveState = m_stateKey;
	CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();
	CPhysicsComponent* pPC = GetComponent<CPhysicsComponent>();
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
				if (pGC->GetAnimation() != nullptr && m_hp != m_lastFrameHp && m_skilltimer > m_skillCooltime)
				{
					pPC->GetSpeed() = pPC->GetSpeed() * 2.0;
					pGC->GetAnimation()->GetAniSecPerFrame() * 2;
					m_skilltimer = 0;
				}

				if (pGC->GetAnimation() != nullptr && m_skilltimer > 2 && pGC->GetAnimation()->GetAniSecPerFrame() != 15)
				{
					pPC->GetSpeed() = pPC->GetSpeed() * 0.5;
					pGC->GetAnimation()->GetAniSecPerFrame() = 15;
				}

				m_stateKey = "Walk";

				if (m_direction.x < 0)
					GetComponent<CGraphicsComponent>()->SetXFlip(true);
				else if (m_direction.x > 0)
					GetComponent<CGraphicsComponent>()->SetXFlip(false);


				m_routeDistance -= GetComponent<CPhysicsComponent>()->GetSpeed() * GET_DT();
			}
			else
				m_stateKey = "Idle";
		}
	}

	if (saveState != m_stateKey)
		StateChangeInit();

	m_lastFrameHp = m_hp;
	m_skilltimer += GET_DT();
}

void CDogMonster::LateUpdate(void)
{
	__super::LateUpdate();
}

void CDogMonster::Release(void)
{
}

void CDogMonster::AddChildAndComponents(void)
{
	__super::AddChildAndComponents();
}

void CDogMonster::InitializeComponents(void)
{
}

void CDogMonster::Die(void)
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
