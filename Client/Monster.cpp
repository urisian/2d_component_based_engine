#include "stdafx.h"
#include "Monster.h"
#include "DataStore.h"
#include "GraphicsComponent.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_objID = OBJID::MONSTER;
	m_dataID = DATAID::MONSTER;

	__super::Initialize();

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

void CMonster::Update(void)
{
	__super::Update();
}

void CMonster::LateUpdate(void)
{
}

void CMonster::Release(void)
{
}
