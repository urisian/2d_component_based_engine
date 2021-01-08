#include "stdafx.h"
#include "InputManager.h"

CInputManager* CInputManager::m_s_pInstance = nullptr;
CInputManager * CInputManager::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CInputManager;

	return m_s_pInstance;
}

void CInputManager::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CInputManager::Initialize(void)
{
}

void CInputManager::Update(void)
{
	m_lastFrameKey = m_key;
	m_key = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_key |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_key |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_key |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_key |= KEY_DOWN;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_key |= KEY_SPACE;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_key |= KEY_RETURN;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_key |= MOUSE_LEFT;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_key |= MOUSE_RIGHT;
	if (GetAsyncKeyState(VK_F1) & 0x8000)
		m_key |= KEY_F1;
	if (GetAsyncKeyState(VK_F2) & 0x8000)
		m_key |= KEY_F2;
	if (GetAsyncKeyState(VK_F3) & 0x8000)
		m_key |= KEY_F3;
	if (GetAsyncKeyState(VK_F4) & 0x8000)
		m_key |= KEY_F4;
	if (GetAsyncKeyState(VK_F5) & 0x8000)
		m_key |= KEY_F5;
}

bool CInputManager::KeyUp(DWORD key)
{
	if ((m_lastFrameKey & key) && !(m_key & key))
		return true;

	return false;
}

bool CInputManager::KeyDown(DWORD key)
{
	if (!(m_lastFrameKey & key) && (m_key & key))
		return true;

	return false;
}

bool CInputManager::KeyPress(DWORD key)
{
	if (m_key & key)
		return true;

	return false;
}


CInputManager::CInputManager()
{
}


CInputManager::~CInputManager()
{
}