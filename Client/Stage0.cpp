#include "stdafx.h"
#include "Stage0.h"
#include "DataStore.h"

#include "Background.h"

CStage0::CStage0()
{
}


CStage0::~CStage0()
{
}

void CStage0::Initialize(void)
{
	std::string backgroundObjKey;
	GET_VALUE(DATAID::STAGE, GetCurClassName(this), "backgroundObjKey", backgroundObjKey);

	m_pBackground = new CBackground(backgroundObjKey);
}

void CStage0::Update(void)
{
}

void CStage0::LateUpdate(void)
{
}

void CStage0::Release(void)
{
}
