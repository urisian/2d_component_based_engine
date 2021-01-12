#include "stdafx.h"
#include "BaseTurret.h"
#include "ObjectManager.h"
#include "DataStore.h"
#include "ClickableComponent.h"
#include "TurretRing.h"

CBaseTurret::CBaseTurret()
{
	Initialize();
}


CBaseTurret::~CBaseTurret()
{
}

void CBaseTurret::Initialize(void)
{
	__super::Initialize();
}

void CBaseTurret::Update(void)
{
	__super::Update();
}

void CBaseTurret::LateUpdate(void)
{
}

void CBaseTurret::Release(void)
{
}

