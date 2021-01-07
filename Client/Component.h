#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"

class CComponent
{
public:
	explicit					CComponent			(void);
	virtual					   ~CComponent			(void);

	const		std::string&	GetComponentType	(void) const;

private:
				std::string		m_componentType;
				CObject*		m_pOwner;
};


#endif