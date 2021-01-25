#pragma once
#include "Unit.h"
class CReinforceUnit :
	public CUnit
{
public:
	CReinforceUnit(int id);
	~CReinforceUnit();

	void			Initialize(void);
	void			Update(void);
	void			LateUpdate(void);
	void			Release(void);

	void			AddChildAndComponents(void);
	void			InitializeComponents(void);
	void			StateChangeInit(void);
	void			FindTarget(void);
	void			MoveTo(D3DXVECTOR3 destPos, std::string nextStateKey);
	D3DXVECTOR3		m_rallyPosition;
	D3DXVECTOR3		m_approachPosition;
	float			m_lifeTime;
	int				m_id;
};

