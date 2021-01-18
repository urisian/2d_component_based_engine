#ifndef FADEOUTEFFECTCOMPONENT_H
#define FADEOUTEFFECTCOMPONENT_H

#include "EffectComponent.h"
class CFadeOutEffectComponent final : public CEffectComponent
{
public:
	explicit					CFadeOutEffectComponent		(CObject* pOwner);
							   ~CFadeOutEffectComponent		(void);

					void		Initialize					(void);
					void		Update						(void);
					void		LateUpdate					(void);
					void		Release						(void);

					void		StateChangeInit				(void);

	GETTOR_SETTOR	(float,		m_startTimer,				StartTimer);
};

#endif