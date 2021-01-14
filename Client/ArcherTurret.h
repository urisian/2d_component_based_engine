#ifndef ARCHERTURRET_H
#define ARCHERTURRET_H

#include "Turret.h"

class CMonster;
class CArcherUnit;

class CArcherTurret final : public CTurret
{
public:
	explicit							CArcherTurret		(void);
									   ~CArcherTurret		(void);

	virtual			void				Initialize			(void);
	virtual			void				Update				(void);
	virtual			void				LateUpdate			(void);
	virtual			void				Release				(void);

	GETTOR_SETTOR	(CMonster*,			m_pTarget,			Target);
	GETTOR_SETTOR	(CArcherUnit*,		m_pArchers[2],		Archer);
};

#endif

