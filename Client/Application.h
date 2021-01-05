#pragma once
class CApplication
{
public:
	static		CApplication*		GetInstance			(void);
	static		void				DestroyInstance		(void);

				void				Initialize			(HINSTANCE hInstance, int nCmdShow);

	const		HWND				GetHandle			(void) const;

				void				Release				(void);



private:
	explicit						CApplication		(void);
	virtual						   ~CApplication		(void);

				ATOM				RegisterWndClass	(HINSTANCE hInstance);
				bool				CreateWndHandle		(HINSTANCE hInstance, int cmdShow);
	static		LRESULT	CALLBACK	WndProc				(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
				HWND				m_hWnd;

				int					m_windowWidth;
				int					m_windowHeight;

				bool				m_isActivated;
				bool				m_fullScreen;

				std::wstring		m_className;
				std::wstring		m_windowName;

	static		CApplication*		m_s_pInstance;
};

