#ifndef MOUSEIDLESTATE_H
#define MOUSEIDLESTATE_H

#include "ObjectState.h"

class CMouseIdleState final : public CObjectState
{
public:
	explicit							CMouseIdleState					(CObject* pOwner);
									   ~CMouseIdleState					(void);

	virtual				void			OnStart							(void);
	virtual				void			OnUpdate						(void);
	virtual				void			OnExit							(void);
};

#endif