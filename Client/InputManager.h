#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class CInputManager
{
public:
	static			CInputManager*			GetInstance			(void);
	static			void					DestroyInstance		(void);

					void					Initialize			(void);
					void					Update				(void);

					bool					KeyUp				(DWORD key);
					bool					KeyDown				(DWORD key);
					bool					KeyPress			(DWORD key);

private:
											CInputManager		(void);
										   ~CInputManager		(void);

private:
					DWORD					m_key;
					DWORD					m_lastFrameKey;
	static			CInputManager*			m_s_pInstance;
};

#endif