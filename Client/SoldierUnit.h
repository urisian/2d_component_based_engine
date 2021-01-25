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

private:
					void			FindTarget				(void);
					void			MoveTo					(D3DXVECTOR3 destPos, std::string nextStateKey);

private:
					D3DXVECTOR3		m_rallyPosition;
	GETTOR_SETTOR	(D3DXVECTOR3,	m_approachPosition,		ApproachPosition);
	GETTOR_SETTOR	(float,			m_reviveTimer,			ReviveTimer);
	GETTOR_SETTOR	(int,			m_id,					ID);
	GETTOR_SETTOR	(bool,			m_rallyChanged,			RallyChanged);

};

#endif