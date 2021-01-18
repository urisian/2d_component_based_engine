#include "stdafx.h"
#include "EffectComponent.h"
#include "DataStore.h"

CEffectComponent::CEffectComponent(CObject* pOwner) : CComponent(pOwner)
{
	m_repeat = 0;
	m_timer = 0;
	m_lifeTime = 0;

	m_killOwner = false;

	m_pNextEffectComponent = nullptr;
}


CEffectComponent::~CEffectComponent()
{
	Release();
}

void CEffectComponent::Initialize(void)
{
	__super::Initialize();

	std::string className = GetCurClassName(this);

	GET_VALUE(DATAID::EFFECT, className, "m_lifeTime", m_lifeTime);
	GET_VALUE(DATAID::EFFECT, className, "m_repeat", m_repeat);
	GET_VALUE(DATAID::EFFECT, className, "m_killOwner", m_killOwner);
}

void CEffectComponent::Update(void)
{
	__super::Update();
}

void CEffectComponent::LateUpdate(void)
{
	__super::LateUpdate();
}

void CEffectComponent::Release(void)
{
	if (m_killOwner)
		m_pOwner->SetNeedToBeDeleted(true);
}
