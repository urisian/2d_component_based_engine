#include "stdafx.h"
#include "FRC.h"
#include "DataStore.h"

CFRC* CFRC::m_s_pInstance = nullptr;

CFRC * CFRC::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CFRC;
	
	return m_s_pInstance;
}

void CFRC::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CFRC::Initialize(void)
{
	GET_VALUE(DATAID::ENGINE, GetCurClassName(this), "m_fps", m_fps);
	QueryPerformanceFrequency(&m_cpuTick);
	QueryPerformanceCounter(&m_beginTime);
	QueryPerformanceCounter(&m_endTime);
}

void CFRC::Update(void)
{
}

bool CFRC::FrameLock(void)
{
	QueryPerformanceCounter(&m_endTime);
	m_spfLimit += float(m_endTime.QuadPart - m_beginTime.QuadPart) / m_cpuTick.QuadPart;
	m_beginTime.QuadPart = m_endTime.QuadPart;

	if ((1.f / m_fps) < m_spfLimit)
	{
		m_deltaTime = m_spfLimit;
		m_spfLimit = 0.f;
		QueryPerformanceFrequency(&m_cpuTick);

		if (m_deltaTime > 0.1)
			return false;


		return true;
	}
	return false;
}

float CFRC::GetDelta(void)
{
	return m_deltaTime;
}

CFRC::CFRC()
{
	m_cpuTick	= {};
	m_beginTime = {};
	m_endTime	= {};

	m_spfLimit	= 0.f;
	m_deltaTime = 0.f;
	m_fps		= 0.f;
}


CFRC::~CFRC()
{
}
