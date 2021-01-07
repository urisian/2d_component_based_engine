#include "stdafx.h"
#include "Component.h"


CComponent::CComponent()
{
	m_componentType = GetCurClassName(this);
}


CComponent::~CComponent()
{
}

const std::string & CComponent::GetComponentType(void) const
{
	return m_componentType;
}

CObject * CComponent::GetOwner(void)
{
	return m_pOwner;
}

void CComponent::SetOwner(CObject * pObject)
{
	m_pOwner = pObject;
}
