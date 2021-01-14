#ifndef WAVE_H
#define WAVE_H

class CStage;
class CMonster;

class CWave
{
public:
	explicit								CWave					(CStage* pStage, int id);
	virtual								   ~CWave					(void);

					void					Initialize				(void);
					void					Update					(void);
					void					LateUpdate				(void);
					void					Release					(void);

private:
					CMonster*				GetMonsterByString		(std::string monsterType);

	GETTOR_SETTOR	(bool,					m_activaed,				Activated);
	GETTOR_SETTOR	(bool,					m_needToBeDeleted,		NeedToBeDeleted);
	
	GETTOR			(float,					m_waveStartTime,		WaveStartTime);
	GETTOR			(float,					m_wavePlayTime,			WavePlayTime);

	GETTOR			(int,					m_id,					ID);
	GETTOR			(int,					m_numOfParty,			NumOfParty);
	
	GETTOR			(CStage*,				m_pStage,				Stage);
	GETTOR (std::vector<MonsterParty*>,		m_vMonsterParty,		MonsterParty);
};

#endif

