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

					void			SetRallyPoint				(void);

					void			MakeSoldier					(void);
					void			MakeRallyCircle				(void);

private:
					CSoldierUnit*	m_pSoldiers[3];

	GETTOR			(CDecoration*,	m_pRallyCircle,				RallyCircle);
	GETTOR			(float,			m_soldierHP,				SoldierHP);

	GETTOR			(int,			m_summonFrameNum,			SummonFrameNum);
	GETTOR			(D3DXVECTOR3,	m_rallyPoint,				RallyPoint);
	GETTOR			(bool,			m_checkRally,				CheckRally);
	GETTOR			(bool,			m_anyRevive,				AnyRevive);
};

#endif

