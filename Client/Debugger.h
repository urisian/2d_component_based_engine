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

					void					AddInfo				(DEBUGID::ID debugID, std::string key, std::string info);

private:
											CDebugger			(void);
										   ~CDebugger			(void);

					void					PrintConsole		(void);
					void					ClearConsole		(void);
					void					ChangeList			(void);

private:
					bool					m_activated;

					//screen reset timer;
					clock_t					m_curTime;
					clock_t					m_prevTime;

					DEBUGID::ID				m_curID;

					D3DXVECTOR3				m_size;

					HANDLE					m_hConsole;
					CONSOLE_CURSOR_INFO		m_consoleCursor;
					SMALL_RECT				m_screenRect;

	std::map<std::string, std::string>		m_mPrintList[DEBUGID::END];

	static			CDebugger*				m_s_pInstance;
};

#endif