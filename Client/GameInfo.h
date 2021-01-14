#ifndef GAMEINFO_H
#define GAMEINFO_H


class CObject;

class CGameInfo
{
public:
	static			CGameInfo*			GetInstance				(void);
	static			void				DestroyInstance			(void);

					void				Initialize				(void);
					void				Update					(void);
					void				LateUpdate				(void);
					void				Release					(void);

	GETTOR_SETTOR	(int,				m_gold,					Gold);
	GETTOR_SETTOR	(CObject*,			m_pFocusedObject,		FocusedObject);
	GETTOR_SETTOR	(int,				m_crystal,				Crystal);
	GETTOR_SETTOR	(int,				m_gameProgress,			GameProgress);


private:
	explicit							CGameInfo				(void);
									   ~CGameInfo				(void);

private:
	static			CGameInfo*			m_s_pInstance;
};

#endif