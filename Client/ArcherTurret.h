#ifndef ARCHERTURRET_H
#define ARCHERTURRET_H

#include "Turret.h"

class CMonster;
class CArcher;
class CStateMachine;

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
	GETTOR_SETTOR	(CArcher*,			m_pArchers[2],		Archer);
	GETTOR_SETTOR	(CStateMachine*,	m_pStateMachine,	StateMachine);
};

#endif

