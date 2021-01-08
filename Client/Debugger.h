#ifndef DEBUGGER_H
#define DEBUGGER_H

class CDebugger
{
public:
	static			CDebugger*				GetInstance			(void);
	static			void					DestroyInstance		(void);

					void					Initialize			(void);
					void					Update				(void);
					void					LateUpdate			(void);
					void					Release				(void);


private:
											CDebugger			(void);
										   ~CDebugger			(void);

					void					PrintConsole		(void);
					void					ClearConsole		(void);

private:
					bool					m_activated;
					int						m_curBufferNum;
					int						m_backBufferNum;

					D3DXVECTOR3				m_size;

					HANDLE					m_hConsole[NUM_OF_BUFFER];
					CONSOLE_CURSOR_INFO		m_consoleCursor;
					SMALL_RECT				m_screenRect;

	static			CDebugger*				m_s_pInstance;
};

#endif