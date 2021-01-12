#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"

class CComponent
{
public:
	explicit						CComponent			(CObject* pOwner);
	virtual						   ~CComponent			(void);

	virtual			void			Initialize			(void) PURE;
	virtual			void			Update				(void) PURE;
	virtual			void			LateUpdate			(void) PURE;
	virtual			void			Release				(void) PURE;

	GETTOR_SETTOR	(bool,			m_needToBeDeleted,	NeedToBeDeleted);
	GETTOR_SETTOR	(CObject*,		m_pOwner,			Owner);
};


#endif