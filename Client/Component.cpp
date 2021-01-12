#include "stdafx.h"
#include "Component.h"


CComponent::CComponent(CObject* pOwner)
{
	m_pOwner = pOwner;
}


CComponent::~CComponent()
{
}


