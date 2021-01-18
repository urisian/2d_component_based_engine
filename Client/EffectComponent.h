#ifndef EFFECTCOMPONENT_H
#define EFFECTCOMPONENT_H

#include "Component.h"


class CEffectComponent abstract : public CComponent
{
public:
	explicit						CEffectComponent	(CObject* pOwner);
	virtual						   ~CEffectComponent	(void);

	virtual			void			Initialize			(void);
	virtual			void			Update				(void);
	virtual			void			LateUpdate			(void);
	virtual			void			Release				(void);

	GETTOR_SETTOR	(int,			m_repeat,			Repeat);
	GETTOR_SETTOR	(float,			m_timer,			Timer);
	GETTOR_SETTOR	(float,			m_lifeTime,			LifeTime);
	GETTOR_SETTOR	(bool,			m_killOwner,		KillOwner);

protected:
	CEffectComponent*				m_pNextEffectComponent;
};

#endif