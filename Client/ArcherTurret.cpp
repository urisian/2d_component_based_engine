#include "stdafx.h"
#include "ArcherTurret.h"
#include "StateMachine.h"
#include "ArcherUnit.h"

CArcherTurret::CArcherTurret()
{
	m_pArchers[0] = nullptr;
	m_pArchers[1] = nullptr;

	Initialize();
}


CArcherTurret::~CArcherTurret()
{
}

void CArcherTurret::Initialize(void)
{
	__super::Initialize();
	m_pArchers[0] = new CArcherUnit(this, 0);
	m_pArchers[1] = new CArcherUnit(this, 1);
}

void CArcherTurret::Update(void)
{
	__super::Update();


	if(m_pTarget != nullptr)
		Shoot();
}

void CArcherTurret::LateUpdate(void)
{
}

void CArcherTurret::Release(void)
{
}

void CArcherTurret::Shoot(void)
{

}
