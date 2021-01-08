#include "stdafx.h"
#include "Debugger.h"
#include "FRC.h"
#include "InputManager.h"

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
	coord.X = 100; coord.Y = 30;
	
	m_screenRect = { 0, 0, 99, 29 };

	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = FALSE;


	


	m_hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
						  				   FILE_SHARE_READ | FILE_SHARE_WRITE,
										   NULL,
										   CONSOLE_TEXTMODE_BUFFER,
										   NULL);

	if (!m_hConsole)
	{
		MessageBox(nullptr, L"Create console handle Failed", L"Debugger.cpp", MB_OK);
		return;
	}

	SetConsoleCursorInfo(m_hConsole, &info);
	SetConsoleScreenBufferSize(m_hConsole, coord);
	SetConsoleWindowInfo(m_hConsole, TRUE, &m_screenRect);



	SetConsoleActiveScreenBuffer(m_hConsole);
}

void CDebugger::Update(void)
{
	PrintConsole();
	ClearConsole();
	ChangeList();
}

void CDebugger::LateUpdate(void)
{
}

void CDebugger::Release(void)
{
}

void CDebugger::AddInfo(DEBUGID::ID debugID, std::string key, std::string info)
{
	m_mPrintList[debugID][key] = info;
}

void CDebugger::PrintConsole(void)
{
	for (auto& info : m_mPrintList[m_curID])
	{
		WriteConsole(m_hConsole, StrToWStr(info.second).c_str(), info.second.size(), nullptr, nullptr);
	}
}

void CDebugger::ClearConsole(void)
{
	m_curTime = clock();

	if (m_curTime - m_prevTime > 1000)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		SMALL_RECT scrollRect;
		COORD scrollTarget;
		CHAR_INFO fill;

		// Get the number of character cells in the current buffer.
		if (!GetConsoleScreenBufferInfo(m_hConsole, &csbi))
		{
			return;
		}

		// Scroll the rectangle of the entire buffer.
		scrollRect.Left = 0;
		scrollRect.Top = 0;
		scrollRect.Right = csbi.dwSize.X;
		scrollRect.Bottom = csbi.dwSize.Y;

		// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
		scrollTarget.X = 0;
		scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

		// Fill with empty spaces with the buffer's default text attribute.
		fill.Char.UnicodeChar = TEXT(' ');
		fill.Attributes = csbi.wAttributes;

		// Do the scroll
		ScrollConsoleScreenBuffer(m_hConsole, &scrollRect, NULL, scrollTarget, &fill);

		m_prevTime = m_curTime;
	}
	COORD cursorPosition;	
	cursorPosition.X = 0;	
	cursorPosition.Y = 0;	
	SetConsoleCursorPosition(m_hConsole, cursorPosition);
}



void CDebugger::ChangeList(void)
{
	DEBUGID::ID checkIfChanged = m_curID;
	if (IMKEY_DOWN(KEY_F1))
		m_curID = DEBUGID::FRAMETIME;
	else if (IMKEY_DOWN(KEY_F2))
		m_curID = DEBUGID::OBJECT_INFO;


	if (checkIfChanged != m_curID)
		m_prevTime = 0;
}

CDebugger::CDebugger()
{
	m_activated = true;
	m_curID = DEBUGID::FRAMETIME;

	m_curTime = 0;
	m_prevTime = 0;
}


CDebugger::~CDebugger()
{
}


