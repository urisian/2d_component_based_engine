// Client.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Client.h"
#include "MainApp.h"
#include "DataStore.h"
#include "Application.h"
#include "FRC.h"
#include "Debugger.h"






int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    // TODO: 여기에 코드를 입력합니다.

	CDataStore::GetInstance()->Initialize();
	CApplication::GetInstance()->Initialize(hInstance, nCmdShow);


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	CMainApp mainApp; 
	mainApp.Initialize();



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
		

		if(CFRC::GetInstance()->FrameLock())
		{	
			mainApp.Update();
			mainApp.LateUpdate();
		}
    }

    return (int) msg.wParam;
}


