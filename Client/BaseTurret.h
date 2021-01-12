#ifndef BASETURRET_H
#define BASETURRET_H

#include "Turret.h"
class CBaseTurret final : public CTurret
{
public:
	explicit					CBaseTurret				(void);
	virtual					   ~CBaseTurret				(void);

				void			Initialize				(void);
				void			Update					(void);
				void			LateUpdate				(void);
				void			Release					(void);
};

#endif