#ifndef UNIT_H
#define UNIT_H

#include "Object.h"

class CMonster;

class CUnit abstract : public CObject
{
public:
	explicit							CUnit			(void);
	virtual							   ~CUnit			(void);

					void				Initialize		(void);
					void				Update			(void);
					void				LateUpdate		(void);
					void				Release			(void);

	GETTOR_SETTOR	(CMonster*,			m_pTarget,		Target);
	GETTOR_SETTOR	(int,				m_level,		Level);

	GETTOR			(int,				m_numOfSkill,	NumOfSkill);
	GETTOR			(float,				m_attackRange,	AttackRange);
	GETTOR			(float,				m_attackSpeed,	AttackSpeed);
	
	GETTOR			(float,				m_dmg,			Dmg);
	GETTOR			(float,				m_magicDmg,		MagicDmg);

	GETTOR			(float,				m_hp,			HP);
	GETTOR			(float,				m_armor,		Armor);
	GETTOR			(float,				m_mr,			MR);
};

#endif