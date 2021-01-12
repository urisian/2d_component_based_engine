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
	virtual			void			LateUpdate				(void) PURE;
	virtual			void			Release					(void);

					bool			GetActivated			(void);
					void			SetActivated			(bool activated);

	std::vector<CObject*>&			GetStateObjects			(void);
protected:
					std::string		m_name;
					bool			m_activated;

					CBackground*	m_pBackground;

	static			CMouse*			m_s_pMouse;
	std::vector<CObject*>			m_vStateObjects;
};

#endif