#include "stdafx.h"
#include "Decoration.h"
#include "GraphicsComponent.h"

CDecoration::CDecoration(std::string objectKey)
{
	m_objectKey = objectKey;
	Initialize();
}


CDecoration::~CDecoration()
{
}

void CDecoration::Initialize(void)
{
	m_objID = OBJID::DECORATION;
	m_dataID = DATAID::DECORATION;

	__super::Initialize();

	AddComponent<CGraphicsComponent>();
}

void CDecoration::Update(void)
{
}

void CDecoration::LateUpdate(void)
{
}

void CDecoration::Release(void)
{
}
