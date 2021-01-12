#ifndef MOUSE_H
#define MOUSE_H

#include "UserInterface.h"
class CMouse : public CUserInterface
{
public:
	explicit							CMouse				(void);
	virtual							   ~CMouse				(void);

	virtual			void				Initialize			(void);
	virtual			void				Update				(void);
	virtual			void				LateUpdate			(void);
	virtual			void				Release				(void);
};

#endif
