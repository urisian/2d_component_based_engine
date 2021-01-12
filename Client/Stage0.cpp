#include "stdafx.h"
#include "Stage0.h"
#include "DataStore.h"
#include "GraphicsComponent.h"
#include "Stage0_Background.h"
#include "BaseTurret.h"
#include "TurretRing.h"

CStage0::CStage0()
{
}


CStage0::~CStage0()
{
}

void CStage0::Initialize(void)
{
	__super::Initialize();

	m_pBackground = new CStage0_Background();

	int numOfDecoration;
	GET_VALUE(DATAID::STAGE, GetCurClassName(this), "numOfDecoration", numOfDecoration);
	
	int numOfBaseTurret;
	GET_VALUE(DATAID::STAGE, GetCurClassName(this), "numOfBaseTurret", numOfBaseTurret);

	for (int i = 0; i < numOfBaseTurret; ++i)
	{
		CBaseTurret* pNewTurret = new CBaseTurret;
		GET_VALUE(DATAID::STAGE, GetCurClassName(this), 
				  "baseTurret" + std::to_string(i) + "_m_pos", pNewTurret->GetPosition());
	}
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
