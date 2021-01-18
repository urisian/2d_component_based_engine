#ifndef ARCHERUNIT_H
#define ARCHERUNIT_h

#include "Unit.h"



class CArcherUnit final : public CUnit
{
public:
	explicit							CArcherUnit				(CObject* pArcherTurret);
	virtual							   ~CArcherUnit				(void);

					void				Initialize				(void);
					void				Update					(void);
					void				LateUpdate				(void);
					void				Release					(void);

					void				UpgradeUnit				(int increase);

					void				AddChildAndComponents	(void);
					void				InitializeComponents	(void);

					void				StateChangeInit			(void);

					void				Shoot					(void);

};

#endif