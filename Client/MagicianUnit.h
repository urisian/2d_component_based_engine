#ifndef MAGICiANUNIT_H
#define MAGICIANUNIT_H

#include "Unit.h"
class CMagicianUnit : public CUnit
{
public:
	explicit						CMagicianUnit			(CObject* pMagicTurret);
	virtual						   ~CMagicianUnit			(void);

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

					void			UpgradeUnit				(int increase);

					void			AddChildAndComponents	(void);
					void			InitializeComponents	(void);

					void			StateChangeInit			(void);

					void			Shoot					(void);
};

#endif