#ifndef EFFECT_H
#define EFFECT_h

#include "Object.h"
class CEffect final : public CObject
{
public:
	explicit						CEffect					(std::string objectKey, std::string stateKey = "",
															 CObject* pParent = nullptr, int repeat = 0, bool killOwner = true);

								   ~CEffect					(void);
	
					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

					void			AddChildAndComponents	(void);
					void			InitializeComponents	(void);

	GETTOR_SETTOR	(int,			m_repeat,			Repeat);
	GETTOR_SETTOR	(float,			m_timer,			Timer);
	GETTOR_SETTOR	(float,			m_lifeTime,			LifeTime);

	GETTOR_SETTOR	(bool,			m_killOwner,		KillOwner);
private:
};

#endif