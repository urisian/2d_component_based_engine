#include "stdafx.h"
#include "Object.h"


CObject::CObject()
{
}


CObject::~CObject()
{
}

bool CObject::GetActivated(void) const
{
	return m_activated;
}

void CObject::SetActivated(bool activated)
{
	m_activated = activated;
}

bool CObject::GetNeedToBeDeleted(void) const
{
	return m_needToBeDeleted;
}

void CObject::SetNeedToBeDeleted(bool needToBeDeleted)
{
	m_needToBeDeleted = needToBeDeleted;
}

