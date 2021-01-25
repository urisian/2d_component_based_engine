#pragma once
#include "UserInterface.h"
class CFireRain : public CUserInterface
{
public:
	CFireRain();
	~CFireRain();

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

