#ifndef GSM_H
#define GSM_H
class CGameState;

class CGSM final
{
public:
	static			CGSM*			GetInstance				(void);
	static			void			DestroyInstance			(void);

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

	GETTOR_SETTOR	(CGameState*,	m_pCurState,			CurState);
	GETTOR_SETTOR	(CGameState*,	m_pNextState,			NextState);
	GETTOR_SETTOR	(bool,			m_needToBeClean,		NeedToBeClean);

private:
									CGSM					(void);
								   ~CGSM					(void);

private:
	std::stack<CGameState*>			m_sStateStack;
	static			CGSM*			m_s_pInstance;

public:
	template<typename T>
	void PushGameState(bool needToBeClean)
	{
		T* pGameState = new T;
		m_needToBeClean = needToClean;
		m_pNextState = pGameState;
	}
};


#endif