#include "stdafx.h"
#include "Unit.h"
#include "DataStore.h"
#include "Monster.h"
#include "GraphicsComponent.h"

CUnit::CUnit()
{
}


CUnit::~CUnit()
{
	Release();
}

void CUnit::Initialize(void)
{
	m_objID = OBJID::UNIT;
	m_dataID = DATAID::UNIT;

	__super::Initialize();

	GET_VALUE(m_dataID, m_objectKey, "m_level", m_level);

	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_numOfSkill", m_numOfSkill);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_attackRange", m_attackRange);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_attackSpeed", m_attackSpeed);

	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_dmg", m_dmg);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_magicDmg", m_magicDmg);
												   
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_hp", m_hp);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_armor", m_armor);
	GET_VALUE(m_dataID, m_objectKey, m_stateKey + "_m_mr", m_mr);

	AddComponent<CGraphicsComponent>();
}

void CUnit::Update(void)
{
	__super::Update();
}

void CUnit::LateUpdate(void)
{
}

void CUnit::Release(void)
{
}


