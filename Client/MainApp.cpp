#include "stdafx.h"
#include "MainApp.h"
#include "Application.h"
#include "GraphicsManager.h"
#include "ObjectManager.h"
#include "TextureStore.h"
#include "DataStore.h"
#include "Application.h"
#include "InputManager.h"
#include "FRC.h"
#include "GSM.h"
#include "Debugger.h"

CMainApp::CMainApp()
{
}


CMainApp::~CMainApp()
{
	Release();
}

void CMainApp::Initialize(void)
{
	CObjectManager::GetInstance()->Initialize();
	CGraphicsManager::GetInstance()->Initialize();
	CTextureStore::GetInstance()->Initialize();
	CInputManager::GetInstance()->Initialize();
	CFRC::GetInstance()->Initialize();
	CGSM::GetInstance()->Initialize();
	CDebugger::GetInstance()->Initialize();
}

void CMainApp::Update(void)
{
#ifdef GENERAL_DEBUG
	DWORD curTime = clock();
	DWORD prevTime = 0;
#endif


	CObjectManager::GetInstance()->Update();
#ifdef GENERAL_DEBUG
	prevTime = curTime;
	curTime = clock();

	ADD_DEBUG_INFO(DEBUGID::FRAMETIME, "ObjectManager_Update","Time spent on ObjectManager Update is " 
		+ std::to_string(curTime-prevTime) + "\n");
#endif


	CGraphicsManager::GetInstance()->Render();
#ifdef GENERAL_DEBUG
	prevTime = curTime;
	curTime = clock();

	ADD_DEBUG_INFO(DEBUGID::FRAMETIME, "GraphicManager_Render", "Time spent on GraphicsManager_Render is "
		+ std::to_string(curTime - prevTime) + "\n");
#endif


	CInputManager::GetInstance()->Update();
#ifdef GENERAL_DEBUG
	prevTime = curTime;
	curTime = clock();

	ADD_DEBUG_INFO(DEBUGID::FRAMETIME, "InputManager_Update", "Time spent on InputManager_Update is "
		+ std::to_string(curTime - prevTime) + "\n");
#endif


	CGSM::GetInstance()->Update();
#ifdef GENERAL_DEBUG
	prevTime = curTime;
	curTime = clock();

	ADD_DEBUG_INFO(DEBUGID::FRAMETIME, "GSM_Update", "Time spent on GSM_Update is "
		+ std::to_string(curTime - prevTime) + "\n");
#endif


	CDebugger::GetInstance()->Update();
}

void CMainApp::LateUpdate(void)
{
	CObjectManager::GetInstance()->LateUpdate();
	CGSM::GetInstance()->LateUpdate();
	CDebugger::GetInstance()->LateUpdate();
}

void CMainApp::Release(void)
{
	CGraphicsManager::GetInstance()->DestroyInstance();
	CObjectManager::GetInstance()->DestroyInstance();

	CTextureStore::GetInstance()->DestroyInstance();
	CDataStore::GetInstance()->DestroyInstance();

	CApplication::GetInstance()->DestroyInstance();
}
