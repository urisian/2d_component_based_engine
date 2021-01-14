#ifndef STAGE_H
#define STAGE_H

#include "GameState.h"

class CWave;

class CStage : public CGameState
{
public:
	explicit										CStage				(void);
	virtual										   ~CStage				(void);

	virtual			void							Initialize			(void);
	virtual			void							Update				(void);
	virtual			void							LateUpdate			(void);
	virtual			void							Release				(void);

protected:
	virtual			void							SpawnWave			(void);


	GETTOR			(float,							m_playTime,			PlayTime);

	GETTOR (std::vector<CWave*>,					m_vWave,			Wave);
	GETTOR (std::vector<std::queue<D3DXVECTOR3>>,	m_vqRoute,			Route);
};

#endif