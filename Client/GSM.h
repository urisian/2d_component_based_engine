#ifndef GSM_H
#define GSM_H
class CGameState;

class CGSM
{
public:
	static			CGSM*			GetInstance				(void);
	static			void			DestroyInstance			(void);

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

private:
									CGSM					(void);
								   ~CGSM					(void);

private:
					bool			m_needToBeCleaned;

					CGameState*		m_pCurState;
					CGameState*		m_pNextState;

	std::stack<CGameState*>			m_sStateStack;
	static			CGSM*			m_s_pInstance;

public:
	template<typename T>
	void PushGameState(bool needToClean)
	{
		T* pGameState = new T;
		m_needToBeCleaned = needToClean;
		m_pNextState = pGameState;
	}
};


#endif