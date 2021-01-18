#ifndef KILLOWNEREFFECTCOMPONENT_H
#define KILLOWNEREFFECTCOMPONENT_H

#include "EffectComponent.h"
class CKillOwnerEffectComponent final : public CEffectComponent
{
public:
	explicit					CKillOwnerEffectComponent	(CObject* pOwner);
							   ~CKillOwnerEffectComponent	(void);

					void		Initialize					(void);
					void		Update						(void);
					void		LateUpdate					(void);
					void		Release						(void);

					void		StateChangeInit				(void);
};

#endif