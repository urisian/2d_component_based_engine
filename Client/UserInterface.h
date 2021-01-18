#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Object.h"

class CUserInterface abstract : public CObject
{
public:
	explicit							CUserInterface			(void);
	virtual							   ~CUserInterface			(void);

	virtual			void				Initialize				(void);
	virtual			void				Update					(void);
	virtual			void				LateUpdate				(void);
	virtual			void				Release					(void);

	virtual			void				AddChildAndComponents	(void);
	virtual			void				InitializeComponents	(void) PURE;
};

#endif