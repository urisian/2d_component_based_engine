#ifndef SOLDIERUNIT_H
#define SOLDIERUNIT_H

#include "Unit.h"
class CSoldierUnit final : public CUnit
{
public:
	explicit						CSoldierUnit			(CObject* pBarrackTurret);
	virtual						   ~CSoldierUnit			(void);

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

					void			UpgradeUnit				(int increase);

					void			AddChildAndComponents	(void);
					void			InitializeComponents	(void);
					void			StateChangeInit			(void);

					void			Revive					(void);

					void			SetRallyPosition		(D3DXVECTOR3 rallyPoint);

	GETTOR_SETTOR	(int,			m_id,					ID);

private:
					D3DXVECTOR3		m_rallyPosition;

};

#endif