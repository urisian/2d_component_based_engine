#ifndef OBJECTSTATE_H
#define OBJECTSTATE_H

class CObject;

class CObjectState abstract
{
public:
	explicit							CObjectState		(CObject* pOwner);
	virtual							   ~CObjectState		(void);

	virtual				void			OnStart				(void) PURE;
	virtual				void			OnUpdate			(void) PURE;
	virtual				void			OnExit				(void) PURE;

	GETTOR_SETTOR		(CObject*,		m_pOwner,			Owner);
};

#endif