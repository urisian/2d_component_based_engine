#ifndef BARRACKTURRET_H
#define BARRACKTURRET_H

#include "Turret.h"

class CSoldierUnit;

class CBarrackTurret final : public CTurret
{
public:
	explicit						CBarrackTurret				(void);
								   ~CBarrackTurret				(void);

					void			Initialize					(void);
					void			Update						(void);
					void			LateUpdate					(void);
					void			Release						(void);

					void			UpgradeTurret				(int increase = 1);

					void			AddChildAndComponents		(void);
					void			InitializeComponents		(void);



private:
					CSoldierUnit*	m_pSoldiers[3];


	GETTOR_SETTOR	(int,			m_numOfAliveSoldier,		NumOfAliveSoldier);
	GETTOR			(int,			m_summonFrameNum,			SummonFrameNum);
	GETTOR			(D3DXVECTOR3,	m_rallyPoint,				RallyPoint);
};

#endif