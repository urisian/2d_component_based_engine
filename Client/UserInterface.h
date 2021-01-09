#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Object.h"

class CUserInterface : public CObject
{
public:
	explicit							CUserInterface		(std::string objectKey);
	virtual							   ~CUserInterface		(void);

	virtual			void				Initialize			(void);
	virtual			void				Update				(void);
	virtual			void				LateUpdate			(void);
	virtual			void				Release				(void);
};

#endif