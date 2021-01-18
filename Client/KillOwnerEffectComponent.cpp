#include "stdafx.h"
#include "KillOwnerEffectComponent.h"
#include "DataStore.h"

CKillOwnerEffectComponent::CKillOwnerEffectComponent(CObject* pOwner) : CEffectComponent(pOwner)
{
}


CKillOwnerEffectComponent::~CKillOwnerEffectComponent()
{
	Release();
}

void CKillOwnerEffectComponent::Initialize(void)
{
	__super::Initialize();
	std::string className = GetCurClassName(this);

}

void CKillOwnerEffectComponent::Update(void)
{
	__super::Update();
}

void CKillOwnerEffectComponent::LateUpdate(void)
{
	__super::LateUpdate();
	if (m_timer >= m_lifeTime)
	{
		m_needToBeDeleted = true;
	}
}

void CKillOwnerEffectComponent::Release(void)
{
	m_pOwner->SetNeedToBeDeleted(true);
}

void CKillOwnerEffectComponent::StateChangeInit(void)
{
}
