#pragma once
#include "UserInterface.h"

class CReinforce : public CUserInterface
{
public:
	CReinforce();
	~CReinforce();

	void				Initialize(void);
	void				Update(void);
	void				LateUpdate(void);
	void				Release(void);

	void				AddChildAndComponents(void);
	void				InitializeComponents(void);

	void				Selected(void);

	GETTOR(float, m_cooltime, Cooltime);
	GETTOR(float, m_timer, Timer);

};

