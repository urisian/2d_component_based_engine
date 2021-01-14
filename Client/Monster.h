#ifndef MONSTER_H
#define MONSTER_H

#include "Object.h"

class CUnit;

class CMonster : public CObject
{
public:
	explicit									CMonster			(void);
	virtual							   		   ~CMonster			(void);

					void						Initialize			(void);
					void						Update				(void);
					void						LateUpdate			(void);
					void						Release				(void);

	GETTOR_SETTOR	(CUnit*,					m_pTarget,			Target);

	GETTOR			(int,						m_numOfSkill,		NumOfSkill);
	GETTOR			(float,						m_attackRange,		AttackRange);
	GETTOR			(float,						m_attackSpeed,		AttackSpeed);
	
	GETTOR			(float,						m_dmg,				Dmg);
	GETTOR			(float,						m_magicDmg,			MagicDmg);

	GETTOR			(float,						m_hp,				HP);
	GETTOR			(float,						m_armor,			Armor);
	GETTOR			(float,						m_mr,				MR);	

	GETTOR			(std::queue<D3DXVECTOR3>,	m_qRoute,			Route);
};

#endif