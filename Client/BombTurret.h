#ifndef BOMBTURRET_H
#define BOMBTURRET_H

#include "Turret.h"
class CBombTurret : public CTurret
{
public:
	explicit					CBombTurret					(void);
	virtual					   ~CBombTurret					(void);

					void		Initialize					(void);
					void		Update						(void);
					void		LateUpdate					(void);
					void		Release						(void);

					void		UpgradeTurret				(int increase = 1);

					void		AddChildAndComponents		(void);
					void		InitializeComponents		(void);

	GETTOR			(int,		m_attackFrameNum,			AttackFrameNum);

};

#endif