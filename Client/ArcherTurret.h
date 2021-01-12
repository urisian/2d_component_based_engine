#ifndef ARCHERTURRET_H
#define ARCHERTURRET_H

#include "Turret.h"

class CArcherTurret final : public CTurret
{
public:
	explicit							CArcherTurret		(void);
									   ~CArcherTurret		(void);

	virtual			void				Initialize			(void);
	virtual			void				Update				(void);
	virtual			void				LateUpdate			(void);
	virtual			void				Release				(void);
};

#endif

