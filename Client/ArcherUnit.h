#ifndef ARCHERUNIT_H
#define ARCHERUNIT_h

#include "Unit.h"



class CArcherUnit final : public CUnit
{
public:
	explicit							CArcherUnit			(CObject* pArcherTurret, int order);
	virtual							   ~CArcherUnit			(void);

					void				Initialize			(void);
					void				Update				(void);
					void				LateUpdate			(void);
					void				Release				(void);

	GETTOR_SETTOR	(int,				m_order,			Order);
};

#endif