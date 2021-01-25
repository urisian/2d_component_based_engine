#include "stdafx.h"
#include "FadeOutEffectComponent.h"
#include "FRC.h"
#include "GraphicsComponent.h"
#include "DataStore.h"


CFadeOutEffectComponent::CFadeOutEffectComponent(CObject* pOwner) : CEffectComponent(pOwner)
{
	m_startTimer = 0;
}


CFadeOutEffectComponent::~CFadeOutEffectComponent()
{
	Release();
}

void CFadeOutEffectComponent::Initialize(void)
{
	__super::Initialize();
	std::string className = GetCurClassName(this);

	GET_VALUE(DATAID::EFFECT, className, "m_startTimer", m_startTimer);
}

void CFadeOutEffectComponent::Update(void)
{
	__super::Update();
}

void CFadeOutEffectComponent::LateUpdate(void)
{
	__super::LateUpdate();
	
	if (m_startTimer <= 0)
	{

		if (m_timer >= m_lifeTime)
		{
			if (m_repeat == 0)
			{
				m_needToBeDeleted = true;
				return;
			}

			--m_repeat;
		}
		m_pOwner->GetComponent<CGraphicsComponent>()->GetColor().a -= 1 / m_lifeTime * GET_DT();


		m_timer += GET_DT();
	}
	else
		m_startTimer -= GET_DT();
}

void CFadeOutEffectComponent::Release(void)
{
	if(m_pNextEffectComponent != nullptr)
		m_pNextEffectComponent->SetActivated(true);
	if (m_killOwner)
		m_pOwner->SetNeedToBeDeleted(true);
}

void CFadeOutEffectComponent::StateChangeInit(void)
{
}
