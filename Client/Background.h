#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Object.h"
class CBackground abstract : public CObject
{
public:
	explicit					CBackground			(void);
							   ~CBackground			(void);
		
	virtual			void		Initialize			(void);
	virtual			void		Update				(void);
	virtual			void		LateUpdate			(void);
	virtual			void		Release				(void);

};

#endif