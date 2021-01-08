#include "stdafx.h"
#include "Object.h"


CObject::CObject()
{
	m_objID				= {};
	m_dataID			= {};

	m_objectKey			= {};
	m_stateKey			= {};

	m_activated			= true;
	m_needToBeDeleted	= false;
}


CObject::~CObject()
{
}

OBJID::ID CObject::GetObjID(void)
{
	return m_objID;
}

DATAID::ID CObject::GetDataID(void)
{
	return m_dataID;
}

std::string & CObject::GetObjectKey(void)
{
	return m_objectKey;
}

std::string & CObject::GetStateKey(void)
{
	return m_stateKey;
}

void CObject::SetStateKey(std::string stateKey)
{
	m_stateKey = stateKey;
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

