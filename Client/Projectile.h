#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Object.h"
class CProjectile : public CObject
{
public:
	explicit							CProjectile				(void);
	virtual							   ~CProjectile				(void);

	virtual			void				Initialize				(void);
	virtual			void				Update					(void);
	virtual			void				LateUpdate				(void);
	virtual			void				Release					(void);


};

#endif