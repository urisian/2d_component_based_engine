// Client.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Client.h"
#include "MainApp.h"
#include "DataStore.h"
#include "Application.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

	CDataStore::GetInstance()->Initialize();
	CApplication::GetInstance()->Initialize(hInstance, nCmdShow);


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	CMainApp tMainApp; 
	tMainApp.Ready_MainApp(); 

	DWORD dwOldTime = GetTickCount(); 
    while (msg.message != WM_QUIT)
    {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		if(dwOldTime + 10 < GetTickCount())
		{
			// 실제 게임 구동. 
			tMainApp.Update_MainApp();
			tMainApp.Late_Update_MainApp();
			tMainApp.Render_MainApp();
			dwOldTime = GetTickCount(); 
		}

    }

    return (int) msg.wParam;
}


