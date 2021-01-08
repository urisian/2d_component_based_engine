#include "stdafx.h"
#include "Debugger.h"
#include "FRC.h"

CDebugger* CDebugger::m_s_pInstance = nullptr;
CDebugger * CDebugger::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CDebugger;
	return m_s_pInstance;
}

void CDebugger::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CDebugger::Initialize(void)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	COORD coord;
	coord.X = 300; coord.Y = 600;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	
	m_screenRect.Left = 0; m_screenRect.Right = 300 - 1; 
	m_screenRect.Top = 0; m_screenRect.Bottom = 600 - 1 ;

	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;


	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &m_screenRect);

	for (int i = 0; i < NUM_OF_BUFFER; ++i)
	{
		m_hConsole[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
												  FILE_SHARE_READ | FILE_SHARE_WRITE,
												  NULL,
												  CONSOLE_TEXTMODE_BUFFER,
												  NULL);

		if (!m_hConsole[i])
		{
			MessageBox(nullptr, L"Create console handle Failed", L"Debugger.cpp", MB_OK);
			return;
		}

		SetConsoleCursorInfo(m_hConsole[i], &info);
	}

	m_curBufferNum	= 0;
	m_backBufferNum = 1;
}

void CDebugger::Update(void)
{

	if (m_curBufferNum == 0)
	{
		m_curBufferNum = 1;
		m_backBufferNum = 0;
	}
	else
	{
		m_curBufferNum = 0;
		m_backBufferNum = 1;
	}
	
	PrintConsole();
	ClearConsole();
}

void CDebugger::LateUpdate(void)
{
}

void CDebugger::Release(void)
{
}

void CDebugger::PrintConsole(void)
{
	
	SetConsoleWindowInfo(m_hConsole[m_curBufferNum], TRUE, &m_screenRect);
	if (!SetConsoleActiveScreenBuffer(m_hConsole[m_curBufferNum]))
	{
		MessageBox(nullptr, L"Set console screen buffer Failed", L"Debugger.cpp", MB_OK);
		return;
	}

	CFRC::GetInstance()->GetDelta();
	for (int i = 0; i < 100; ++i)
	{
		std::string a = std::to_string(CFRC::GetInstance()->GetDelta());

		if (i % 9 == 0)
			a += "\n";
		WriteConsole(m_hConsole[m_curBufferNum], StrToWStr(a).c_str(), a.size(), nullptr, nullptr);
	}
}

void CDebugger::ClearConsole(void)
{
	COORD cursorPosition;	
	cursorPosition.X = 0;	
	cursorPosition.Y = 0;	
	SetConsoleCursorPosition(m_hConsole[m_curBufferNum], cursorPosition);
}

CDebugger::CDebugger()
{
}


CDebugger::~CDebugger()
{
}


