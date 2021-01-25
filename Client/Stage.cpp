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
	Release();
}

void CStage::Initialize(void)
{
	__super::Initialize();

	SetupBaseTurret();
	SetupRoutes();
	SetupWaves();

	m_curWaveNum = 0;
}

void CStage::Update(void)
{
	ADD_DEBUG_INFO(DEBUGID::OBJECT_INFO, "PLAYTIME", std::to_string(m_playTime));
	m_playTime += GET_DT();

	for (auto& wave : m_vWave)
	{
		if (!wave->GetActivated() && wave->GetWaveStartTime() <= m_playTime)
		{
			wave->SetActivated(true);
			++m_curWaveNum;
		}

		if (wave->GetActivated())
			wave->Update();
	}
}

void CStage::LateUpdate(void)
{
	__super::LateUpdate();

	for (auto& it = m_vWave.begin(); it != m_vWave.end();)
	{
		if (!(*it)->GetNeedToBeDeleted() && (*it)->GetActivated())
			(*it)->LateUpdate();

		if ((*it)->GetNeedToBeDeleted())
		{
			SAFE_DELETE(*it);
			it = m_vWave.erase(it);
		}
		else
			++it;
	}
}

void CStage::Release(void)
{
	for (auto& wave : m_vWave)
		SafeDelete(wave);
}

void CStage::SetupBaseTurret(void)
{
	int numOfBaseTurret;
	GET_VALUE(DATAID::STAGE, m_name, "numOfBaseTurret", numOfBaseTurret);

	for (int i = 0; i < numOfBaseTurret; ++i)
	{
		CBaseTurret* pNewTurret = new CBaseTurret;
		GET_VALUE(DATAID::STAGE, m_name, "baseTurret" + std::to_string(i) + "_m_pos", pNewTurret->GetPosition());
		pNewTurret->AddChildAndComponents();
	}
}

void CStage::SetupRoutes(void)
{
	int numOfRoute;
	GET_VALUE(DATAID::STAGE, m_name, "numOfRoute", numOfRoute);
	for (int i = 0; i < numOfRoute; ++i)
	{
		int numOfPointInRoute;
		GET_VALUE(DATAID::STAGE, m_name, "numOfPointInRoute" + std::to_string(i), numOfPointInRoute);
		
		RouteInfo routeInfo;
		for (int j = 0; j < numOfPointInRoute; ++j)
		{
			D3DXVECTOR3 routePoint;
			GET_VALUE(DATAID::STAGE, m_name, "Route" + std::to_string(i) + 
											 "_routePoint" + std::to_string(j), routePoint);

			routeInfo.routePoints.push_back(routePoint);

			if (j > 0)
				routeInfo.distanceFromGoal += D3DXVec3Length(&(routeInfo.routePoints[j] - routeInfo.routePoints[j - 1]));
		}

		m_vRouteInfo.push_back(routeInfo);
	}
}

void CStage::SetupWaves(void)
{
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
