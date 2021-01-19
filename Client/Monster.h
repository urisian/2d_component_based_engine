#ifndef MONSTER_H
#define MONSTER_H

#include "Object.h"

class CUnit;

class CMonster abstract : public CObject
{
public:
	explicit							CMonster				(void);
	virtual					   		   ~CMonster				(void);

	virtual			void				Initialize				(void);
	virtual			void				Update					(void);
	virtual			void				LateUpdate				(void);
	virtual			void				Release					(void);
	
	virtual			void				AddChildAndComponents	(void);
	virtual			void				InitializeComponents	(void) PURE;
	
protected:
	virtual			void				ReadDataFromStore		(void);
	virtual			void				Die						(void);
	
	GETTOR_SETTOR	(unsigned int,		m_routeIndex,			RouteIndex);
	GETTOR_SETTOR	(float,				m_routeDistance,		RouteDistance);
	GETTOR_SETTOR	(CUnit*,			m_pTarget,				Target);

	GETTOR			(int,				m_numOfSkill,			NumOfSkill);
	GETTOR			(float,				m_attackRange,			AttackRange);
	GETTOR			(float,				m_attackCooltime,		AttackCooltime);
	
	GETTOR			(float,				m_dmg,					Dmg);
	GETTOR			(float,				m_magicDmg,				MagicDmg);

	GETTOR			(float,				m_hp,					HP);
	GETTOR			(float,				m_armor,				Armor);
	GETTOR			(float,				m_mr,					MR);	
	

	
	GETTOR			(RouteInfo*,		m_pRouteInfo,			RouteInfo);

	
};

#endif