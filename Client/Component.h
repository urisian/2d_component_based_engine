#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"

class CComponent abstract
{
public:
	explicit						CComponent			(CObject* pOwner);
	virtual						   ~CComponent			(void);

	virtual			void			Initialize			(void);
	virtual			void			Update				(void);
	virtual			void			LateUpdate			(void) PURE;
	virtual			void			Release				(void) PURE;

	virtual			void			StateChangeInit		(void) PURE;

	GETTOR_SETTOR	(bool,			m_activated,		Activated);
	GETTOR_SETTOR	(bool,			m_needToBeDeleted,	NeedToBeDeleted);
	GETTOR_SETTOR	(CObject*,		m_pOwner,			Owner);
};


#endif