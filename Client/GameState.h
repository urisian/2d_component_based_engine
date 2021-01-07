#ifndef GAMESTATE_H
#define GAMESTATE_H

class CObject;
class CBackground;

class CGameState
{
public:
	explicit						CGameState				(void);
	virtual						   ~CGameState				(void);

	virtual			void			Initialize				(void) PURE;
	virtual			void			Update					(void) PURE;
	virtual			void			LateUpdate				(void) PURE;
	virtual			void			Release					(void) PURE;

					bool			GetActivated			(void);
					void			SetActivated			(bool activated);
protected:
					std::string		m_name;
					bool			m_activated;

					CBackground*	m_pBackground;

	std::vector<CObject*>			m_vStateObjects;
};

#endif