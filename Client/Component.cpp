#include "stdafx.h"
#include "Component.h"


CComponent::CComponent(CObject* pOwner)
{
	m_pOwner = pOwner;
	m_needToBeDeleted = false;
	m_activated = true;
}


CComponent::~CComponent()
{
}

void CComponent::Initialize(void)
{
	m_activated = m_pOwner->GetActivated();
}

void CComponent::Update(void)
{
}

void CComponent::LateUpdate(void)
{
	m_activated = m_pOwner->GetActivated();
}


