#include "stdafx.h"
#include "Component.h"


CComponent::CComponent()
{
}


CComponent::~CComponent()
{
}

const std::string & CComponent::GetComponentType(void) const
{
	return m_componentType;
}
