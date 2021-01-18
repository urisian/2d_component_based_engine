#ifndef ARCHERTURRET_H
#define ARCHERTURRET_H

#include "Turret.h"

class CArcherUnit;

class CArcherTurret final : public CTurret
{
public:
	explicit							CArcherTurret				(void);
									   ~CArcherTurret				(void);

					void				Initialize					(void);
					void				Update						(void);
					void				LateUpdate					(void);
					void				Release						(void);

					void				UpgradeTurret				(int increase = 1);

					void				AddChildAndComponents		(void);
					void				InitializeComponents		(void);

					CArcherUnit**		GetArchers					(void);

	GETTOR			(int,				m_shootTurn,				ShootTurn);;
private:
					CArcherUnit*		m_pArchers[2];
};

#endif

