#ifndef UNIT_H
#define UNIT_H

#include "Object.h"

class CMonster;

class CUnit abstract : public CObject
{
public:
	explicit						CUnit					(void);
	virtual						   ~CUnit					(void);

	virtual			void			Initialize				(void);
	virtual			void			Update					(void);
	virtual			void			LateUpdate				(void);
	virtual			void			Release					(void);

	virtual			void			UpgradeUnit				(int increase = 1);

	virtual			void			AddChildAndComponents	(void);
	virtual			void			InitializeComponents	(void) PURE;
	virtual			void			StateChangeInit			(void);

protected:
	virtual			void			ReadDataFromStore		(void);

	GETTOR_SETTOR	(CObject*,		m_pTarget,				Target);
	GETTOR_SETTOR	(int,			m_level,				Level);

	GETTOR			(int,			m_numOfSkill,			NumOfSkill);
	GETTOR			(float,			m_attackRange,			AttackRange);

	GETTOR			(float,			m_attackTimer,			AttackTimer);
	GETTOR			(float,			m_attackSpeed,			AttackSpeed);
	
	GETTOR			(float,			m_dmg,					Dmg);
	GETTOR			(float,			m_magicDmg,				MagicDmg);

	GETTOR			(float,			m_hp,					HP);
	GETTOR			(float,			m_armor,				Armor);
	GETTOR			(float,			m_mr,					MR);

};

#endif