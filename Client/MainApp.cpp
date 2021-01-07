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
}

void CMainApp::Update(void)
{
	CObjectManager::GetInstance()->Update();
	CGraphicsManager::GetInstance()->Render();
	CInputManager::GetInstance()->Update();
	CGSM::GetInstance()->Update();
}

void CMainApp::LateUpdate(void)
{
	CObjectManager::GetInstance()->LateUpdate();
	CGSM::GetInstance()->LateUpdate();
}

void CMainApp::Release(void)
{
	CGraphicsManager::GetInstance()->DestroyInstance();
	CObjectManager::GetInstance()->DestroyInstance();

	CTextureStore::GetInstance()->DestroyInstance();
	CDataStore::GetInstance()->DestroyInstance();

	CApplication::GetInstance()->DestroyInstance();
}
