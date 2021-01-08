#include "stdafx.h"
#include "DebugPrinter.h"


CDebugPrinter::CDebugPrinter()
{
	m_ltPosition.x = 0;
	m_ltPosition.y = 0;
	m_rbPosition.x = 1;
	m_rbPosition.y = 1;
}

CDebugPrinter::CDebugPrinter(POINT & ltp, POINT & rbp)
{
	m_ltPosition = ltp;
	m_rbPosition = rbp;
}

CDebugPrinter::CDebugPrinter(D3DXVECTOR2 & ltp, D3DXVECTOR2 & rbp)
{
	m_ltPosition.x = static_cast<long>(ltp.x);
	m_ltPosition.y = static_cast<long>(ltp.y);
	m_rbPosition.x = static_cast<long>(rbp.x);
	m_rbPosition.y = static_cast<long>(rbp.y);
}

CDebugPrinter::CDebugPrinter(int ltpx, int ltpy, int rbpx, int rbpy)
{
	m_ltPosition.x = ltpx;
	m_ltPosition.y = ltpy;
	m_rbPosition.x = rbpx;
	m_rbPosition.y = rbpy;
}


CDebugPrinter::~CDebugPrinter()
{
}

void CDebugPrinter::Init(void)
{
	m_size.x = m_rbPosition.x - m_ltPosition.x;
	m_size.y = m_rbPosition.y - m_ltPosition.y;

	if (m_size.x <= 0 || m_size.y <= 0)
	{
		MessageBox(nullptr, L"Something is wrong with debugprinter Init", L"DebugPrinter.cpp", MB_OK);
		return;
	}

	m_bufferSize.X = (short)m_size.x;
	m_bufferSize.Y = (short)m_size.y;

	m_bufferChord.X = 0;
	m_bufferChord.Y = 0;

	if (m_pPrintBuffer)
		delete[] m_pPrintBuffer;

	m_pPrintBuffer = new CHAR_INFO[m_size.x * m_size.y];

	m_scrWriteRect.Left = static_cast<short>(m_ltPosition.x);
	m_scrWriteRect.Right = static_cast<short>(300 - 1);

	m_scrWriteRect.Top = static_cast<short>(m_ltPosition.y);
	m_scrWriteRect.Bottom = static_cast<short>(600 - 1);

	for (unsigned index = 0; index < static_cast<unsigned>(m_bufferSize.X * m_bufferSize.Y); ++index)
	{
		m_pPrintBuffer[index].Attributes = 0;
		m_pPrintBuffer[index].Char.AsciiChar = 0;
		m_pPrintBuffer[index].Char.UnicodeChar = 0;
	}
}

void CDebugPrinter::StringSet(const std::string & str)
{
	m_stringToPrint.assign(str);

	unsigned bufferSize = static_cast<unsigned>(m_size.x * m_size.y);
	unsigned strSize	= m_stringToPrint.size();

	if (strSize > bufferSize)
	{

	}
}

void CDebugPrinter::StringAdd(const std::string & str)
{
}

void CDebugPrinter::Translate(void)
{
}

void CDebugPrinter::Print(HANDLE * hMainConsole)
{
}

void CDebugPrinter::HighLight(void)
{
}

void CDebugPrinter::UnHighLight(void)
{
}

void CDebugPrinter::SetAttributes(void)
{
}
