// Client.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
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


    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

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


