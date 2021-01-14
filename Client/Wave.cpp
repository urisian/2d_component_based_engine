#include "stdafx.h"
#include "Wave.h"
#include "DataStore.h"
#include "Stage.h"
#include "FRC.h"
#include "Monster.h"
#include "OakMonster.h"

CWave::CWave(CStage* pStage, int id)
{
	m_pStage = pStage;
	m_id = id;

	m_wavePlayTime = 0;

	m_activaed = false;
	m_needToBeDeleted = false;

	Initialize();
}


CWave::~CWave()
{
}

void CWave::Initialize(void)
{
	GET_VALUE(DATAID::STAGE, m_pStage->GetName(), "wave" + std::to_string(m_id) + "_waveStartTime", m_waveStartTime);
	GET_VALUE(DATAID::STAGE, m_pStage->GetName(), "wave" + std::to_string(m_id) + "_numOfParty", m_numOfParty);

	for (int i = 0; i < m_numOfParty; ++i)
	{
		MonsterParty* pMonsterParty = new MonsterParty;
		GET_VALUE(DATAID::STAGE, m_pStage->GetName(), "wave" + std::to_string(m_id) + "_party" + std::to_string(i) + "_monsterType", pMonsterParty->monsterType);
		GET_VALUE(DATAID::STAGE, m_pStage->GetName(), "wave" + std::to_string(m_id) + "_party" + std::to_string(i) + "_numOfMonster", pMonsterParty->numOfMonster);
		GET_VALUE(DATAID::STAGE, m_pStage->GetName(), "wave" + std::to_string(m_id) + "_party" + std::to_string(i) + "_routeNum", pMonsterParty->routeNum);
		GET_VALUE(DATAID::STAGE, m_pStage->GetName(), "wave" + std::to_string(m_id) + "_party" + std::to_string(i) + "_spawnStartTime", pMonsterParty->spawnStartTime);
		GET_VALUE(DATAID::STAGE, m_pStage->GetName(), "wave" + std::to_string(m_id) + "_party" + std::to_string(i) + "_spawnCoolTime", pMonsterParty->spawnCoolTime);
		

		m_vMonsterParty.push_back(pMonsterParty);
	}
}

void CWave::Update(void)
{
	m_wavePlayTime += GET_DT();

	for (int i = 0; i < m_numOfParty; ++i)
	{
		if (m_vMonsterParty[i]->spawnStartTime <= m_wavePlayTime)
			m_vMonsterParty[i]->activated = true;

		if (m_vMonsterParty[i]->activated)
		{
			m_vMonsterParty[i]->spawnStartTime += GET_DT();

			if (m_vMonsterParty[i]->numOfMonster > 0 && (m_vMonsterParty[i]->spawnStartTime >= m_vMonsterParty[i]->spawnCoolTime))
			{
				CMonster* pNewMonster = GetMonsterByString(m_vMonsterParty[i]->monsterType);
				pNewMonster->GetRoute() = m_pStage->GetRoute()[m_vMonsterParty[i]->routeNum];

				m_vMonsterParty[i]->spawnStartTime = 0.f;

				--m_vMonsterParty[i]->numOfMonster;
			}

			m_vMonsterParty[i]->spawnStartTime += GET_DT();
		}
	}
}

void CWave::LateUpdate(void)
{
}

void CWave::Release(void)
{
}

CMonster * CWave::GetMonsterByString(std::string monsterType)
{
	CMonster* pMonster = nullptr;
	if (monsterType == "OakMonster")
		pMonster = new COakMonster;

	return pMonster;
}
