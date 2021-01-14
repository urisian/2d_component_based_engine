#include "stdafx.h"
#include "Stage.h"
#include "DataStore.h"
#include "Wave.h"
#include "Debugger.h"
#include "FRC.h"
#include "BaseTurret.h"

CStage::CStage()
{
	m_playTime = 0;
}


CStage::~CStage()
{
}

void CStage::Initialize(void)
{
	__super::Initialize();

	int numOfBaseTurret;
	GET_VALUE(DATAID::STAGE, m_name, "numOfBaseTurret", numOfBaseTurret);

	for (int i = 0; i < numOfBaseTurret; ++i)
	{
		CBaseTurret* pNewTurret = new CBaseTurret;
		GET_VALUE(DATAID::STAGE, m_name, "baseTurret" + std::to_string(i) + "_m_pos", pNewTurret->GetPosition());
	}

	int numOfRoute;
	GET_VALUE(DATAID::STAGE, m_name, "numOfRoute", numOfRoute);
	for (int i = 0; i < numOfRoute; ++i)
	{
		int numOfPointInRoute;
		GET_VALUE(DATAID::STAGE, m_name, "numOfPointInRoute" + std::to_string(i), numOfPointInRoute);
		
		std::queue<D3DXVECTOR3> routeQueue;
		m_vqRoute.push_back(routeQueue);
		for (int j = 0; j < numOfPointInRoute; ++j)
		{
			D3DXVECTOR3 routePoint;
			GET_VALUE(DATAID::STAGE, m_name, "Route" + std::to_string(i) + 
											 "_routePoint" + std::to_string(j), routePoint);

			m_vqRoute[i].push(routePoint);
		}
	}

	int numOfWave;
	GET_VALUE(DATAID::STAGE, m_name, "numOfWave", numOfWave);
	for (int i = 0; i < numOfWave; ++i)
	{
		CWave* pWave = new CWave(this, i);
		GET_VALUE(DATAID::STAGE, m_name, "wave" + std::to_string(i) + "_waveStartTime", pWave->GetWaveStartTime());
		GET_VALUE(DATAID::STAGE, m_name, "wave" + std::to_string(i) + "_numOfParty", pWave->GetNumOfParty());
		m_vWave.push_back(pWave);
	}
}

void CStage::Update(void)
{
	ADD_DEBUG_INFO(DEBUGID::OBJECT_INFO, "PLAYTIME", std::to_string(m_playTime));
	m_playTime += GET_DT();
}

void CStage::LateUpdate(void)
{
}

void CStage::Release(void)
{
}

void CStage::SpawnWave(void)
{
}
