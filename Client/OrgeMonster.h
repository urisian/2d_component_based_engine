#pragma once
#include "Monster.h"
class COrgeMonster :
	public CMonster
{
public:
	COrgeMonster();
	~COrgeMonster();

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

	virtual			void			AddChildAndComponents	(void);
					void			InitializeComponents	(void);

protected:
					void			Die						(void);
};

