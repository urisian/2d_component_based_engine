#ifndef OAKMONSTER_H
#define OAKMONSTER_H

#include "Monster.h"


class COakMonster final : public CMonster
{
public:
	explicit						COakMonster			(void);
	virtual						   ~COakMonster			(void);

					void			Initialize			(void);
					void			Update				(void);
					void			LateUpdate			(void);
					void			Release				(void);
};

#endif

