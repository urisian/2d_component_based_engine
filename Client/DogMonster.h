#pragma once
#include "Monster.h"
class CDogMonster : public CMonster
{
public:
	CDogMonster();
	~CDogMonster();

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

	virtual			void			AddChildAndComponents	(void);
					void			InitializeComponents	(void);

protected:
					void			Die						(void);
					
					float			m_skilltimer;
					float			m_skillCooltime;
					int				m_lastFrameHp;
};

