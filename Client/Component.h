#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"

class CComponent
{
public:
	explicit					CComponent			(void);
	virtual					   ~CComponent			(void);

	virtual		void			Initialize			(void) PURE;
	virtual		void			Update				(void) PURE;
	virtual		void			LateUpdate			(void) PURE;
	virtual		void			Release				(void) PURE;

	const		std::string&	GetComponentType	(void) const;
				
				CObject*		GetOwner			(void);
				void			SetOwner			(CObject* pObject);

protected:
				std::string		m_componentType;
				CObject*		m_pOwner;
};


#endif