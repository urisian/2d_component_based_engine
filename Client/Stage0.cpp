#include "stdafx.h"
#include "Stage0.h"
#include "DataStore.h"
#include "GraphicsComponent.h"
#include "BaseTurret.h"
#include "TurretRing.h"
#include "Wave.h"


CStage0::CStage0()
{
}


CStage0::~CStage0()
{
}

void CStage0::Initialize(void)
{
	__super::Initialize();
}

void CStage0::Update(void)
{
	__super::Update();

	for (auto& wave : m_vWave)
	{
		if (!wave->GetActivated() && wave->GetWaveStartTime() <= m_playTime)
			wave->SetActivated(true);

		if (wave->GetActivated())
			wave->Update();
	}
}

void CStage0::LateUpdate(void)
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

void CStage0::Release(void)
{
}

void CStage0::SpawnWave(void)
{
}
