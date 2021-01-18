#include "stdafx.h"
#include "Application.h"
#include "Resource.h"
#include "DataStore.h"
#include "FRC.h"

CApplication* CApplication::m_s_pInstance = nullptr;

CApplication * CApplication::GetInstance(void)
{
	if (!m_s_pInstance)
		m_s_pInstance = new CApplication;

	return m_s_pInstance;
}

void CApplication::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CApplication::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	std::string curClassName = GetCurClassName(this);
	GET_VALUE(DATAID::ENGINE, curClassName, "m_className", m_className);
	GET_VALUE(DATAID::ENGINE, curClassName, "m_windowName", m_windowName);
	GET_VALUE(DATAID::ENGINE, curClassName, "m_windowWidth", m_windowWidth);
	GET_VALUE(DATAID::ENGINE, curClassName, "m_windowHeight", m_windowHeight);


	RegisterWndClass(hInstance);
	CreateWndHandle(hInstance, nCmdShow);

	
}

HWND CApplication::GetHandle(void) const
{
	return m_hWnd;
}

int CApplication::GetWndWidth(void) const
{
	return m_windowWidth;
}

int CApplication::GetWndHeight(void) const
{
	return m_windowHeight;
}

bool CApplication::GetFullScreen(void) const
{
	return m_fullScreen;
}

ATOM CApplication::RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL; /*MAKEINTRESOURCEW(IDC_CLIENT);*/
	wcex.lpszClassName = m_className.c_str();
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

bool CApplication::CreateWndHandle(HINSTANCE hInstance, int nCmdShow)
{
	RECT rc = { 0, 0, m_windowWidth, m_windowHeight };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	m_hWnd = CreateWindowW(m_className.c_str(), m_windowName.c_str(),
						   WS_OVERLAPPEDWINDOW, 
						   CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top,
						   nullptr, nullptr, hInstance, nullptr);

	SetWindowPos(m_hWnd, 0, 100, 150, rc.right - rc.left, rc.bottom - rc.top, 0);
	if (!m_hWnd)
		return false;


	ShowCursor(false);
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return true;
}

LRESULT CApplication::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
	}
	break;
	case WM_ACTIVATE:
		if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
		{
			
		}
		else if (wParam == WA_INACTIVE)
		{
			CFRC::GetInstance()->Initialize();
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return 0;
}

void CApplication::Release(void)
{
}

CApplication::CApplication(void)
{
	m_hWnd			= nullptr;

	m_windowWidth	= 0;
	m_windowHeight	= 0;

	m_isActivated	= true;
	m_fullScreen	= false;

	m_className		= L"";
	m_windowName	= L"";
}


CApplication::~CApplication(void)
{
}
