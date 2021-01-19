#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Object.h"


class CProjectile abstract : public CObject
{
public:
	explicit							CProjectile				(CObject* pShooter);
	virtual							   ~CProjectile				(void);

	virtual			void				Initialize				(void);
	virtual			void				Update					(void);
	virtual			void				LateUpdate				(void);
	virtual			void				Release					(void);

	virtual			void				AddChildAndComponents	(void);
	virtual			void				InitializeComponents	(void) PURE;

protected:
	virtual			void				HitTarget				(void);
	virtual			void				AfterHit				(void);
	virtual			void				GiveDamage				(void);

	GETTOR_SETTOR	(CObject*,			m_pTarget,				Target);

	GETTOR			(float,				m_dmg,					Dmg);
	GETTOR			(float,				m_magicDmg,				MagicDmg);	
	GETTOR			(CObject*,			m_pShooter,				Shooter);
};

#endif