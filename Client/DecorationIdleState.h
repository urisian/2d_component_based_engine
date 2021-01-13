#ifndef DECORATIONIDLESTATE_H
#define DECORATIONIDLESTATE_H

#include "ObjectState.h"

class CObject;

class CDecorationIdleState : public CObjectState
{
public:
	explicit							CDecorationIdleState			(CObject* pOwner);
	virtual							   ~CDecorationIdleState			(void);

	virtual				void			OnStart							(void);
	virtual				void			OnUpdate						(void);
	virtual				void			OnExit							(void);
};

#endif