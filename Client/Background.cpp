#include "stdafx.h"
#include "Background.h"
#include "GraphicsComponent.h"
#include "ObjectManager.h"
#include "DataStore.h"

CBackground::CBackground(void)
{	
}


CBackground::~CBackground()
{
}

void CBackground::Initialize(void)
{
	m_objID = OBJID::BACKGROUND;
	m_dataID = DATAID::BACKGROUND;

	__super::Initialize();


	AddComponent<CGraphicsComponent>();
}

void CBackground::Update(void)
{
	GetComponent<CGraphicsComponent>()->Update();
}

void CBackground::LateUpdate(void)
{
}

void CBackground::Release(void)
{
}
