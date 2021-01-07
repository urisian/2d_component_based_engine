#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Object.h"
class CBackground : public CObject
{
public:
	explicit					CBackground			(std::string objectKey, std::string stateKey = "Idle");
	virtual					   ~CBackground			(void);

	virtual			void		Update				(void);
	virtual			void		LateUpdate			(void);
	virtual			void		Release				(void);

};

#endif