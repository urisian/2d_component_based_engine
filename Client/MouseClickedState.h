#ifndef MOUSECLICKEDSTATE_H
#define MOUSECLICKEDSTATE_H

#include "ObjectState.h"

class CMouseClickedState final : public CObjectState
{
public:
	explicit							CMouseClickedState			(CObject* pOwner);
									   ~CMouseClickedState			(void);

	virtual				void			OnStart						(void);
	virtual				void			OnUpdate					(void);
	virtual				void			OnExit						(void);
};

#endif