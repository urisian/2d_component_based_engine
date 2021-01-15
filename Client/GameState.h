#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Mouse.h"

class CObject;
class CBackground;

class CGameState abstract
{
public:
	explicit						CGameState				(void);
	virtual						   ~CGameState				(void);

	virtual			void			Initialize				(void);
	virtual			void			Update					(void) PURE;
	virtual			void			LateUpdate				(void);
	virtual			void			Release					(void);

	GETTOR			(CObject*,		m_pBackground,			Background);
	GETTOR			(std::string,	m_name,					Name);
	GETTOR_SETTOR	(bool,			m_activated,			Activated);

protected:
	static			CMouse*			m_s_pMouse;
};

#endif