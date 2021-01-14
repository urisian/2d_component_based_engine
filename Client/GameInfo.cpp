#include "stdafx.h"
#include "GameInfo.h"
#include "DataStore.h"
#include "InputManager.h"

CGameInfo* CGameInfo::m_s_pInstance = nullptr;

CGameInfo * CGameInfo::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CGameInfo;

	return m_s_pInstance;
}

void CGameInfo::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CGameInfo::Initialize(void)
{
	std::string objectKey = GetCurClassName(this);
	GET_VALUE(DATAID::ENGINE, objectKey, "m_crystal", m_crystal);
	GET_VALUE(DATAID::ENGINE, objectKey, "m_gameProgress", m_gameProgress);
}

void CGameInfo::Update(void)
{
	if (IMKEY_UP(MOUSE_RIGHT) && m_pFocusedObject != nullptr)
	{
		m_pFocusedObject = nullptr;
	}
}

void CGameInfo::LateUpdate(void)
{
}

void CGameInfo::Release(void)
{
}

CGameInfo::CGameInfo()
{
	m_pFocusedObject = nullptr;
	m_crystal = 0;
	m_gameProgress = 0;
	m_gold = 0;
}


CGameInfo::~CGameInfo()
{
}
