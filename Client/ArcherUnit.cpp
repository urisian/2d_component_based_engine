#include "stdafx.h"
#include "ArcherUnit.h"


CArcherUnit::CArcherUnit(CObject* pArcherTurret, int order)
{
	m_pParent = pArcherTurret;
	m_order = order;
	Initialize();
}


CArcherUnit::~CArcherUnit()
{
}

void CArcherUnit::Initialize(void)
{
	__super::Initialize();

	if (m_order == 1)
		m_position.x *= -1;
}

void CArcherUnit::Update(void)
{
	__super::Update();
	m_parentPosition = m_pParent->GetPosition() + m_pParent->GetParentPosition();

}

void CArcherUnit::LateUpdate(void)
{
}

void CArcherUnit::Release(void)
{
}



