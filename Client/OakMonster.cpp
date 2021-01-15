#include "stdafx.h"
#include "OakMonster.h"
#include "PhysicsComponent.h"
#include "Debugger.h"
#include "FRC.h"

COakMonster::COakMonster()
{
	Initialize();
}


COakMonster::~COakMonster()
{
}

void COakMonster::Initialize(void)
{
	__super::Initialize();
}

void COakMonster::Update(void)
{
	__super::Update();

	std::string saveState = m_stateKey;

	if (m_routeIndex < m_pRouteInfo->routePoints.size())
	{
		m_stateKey = "Walk";
		if (m_direction.y < 0 && (abs(m_direction.y) > abs(m_direction.x)))
			m_stateKey += "Down";
		else if (m_direction.y > 0 && (abs(m_direction.y) > abs(m_direction.x)))
			m_stateKey += "Up";
		else
		{
			m_stateKey += "Hor";
			if (m_direction.x < 0 && m_size.x > 0)
				m_size.x *= -1;
			else if (m_direction.x > 0 && m_size.x < 0)
				m_size.x *= -1;
		}

		m_routeDistance -= GetComponent<CPhysicsComponent>()->GetSpeed() * GET_DT();
	}
	else
		m_stateKey = "Idle";

	if (saveState != m_stateKey)
		StateChangeInit();

	
	ADD_DEBUG_INFO(DEBUGID::OBJECT_INFO, "Oak", "distanceLeft : " + std::to_string(m_routeDistance) + "\n");
}

void COakMonster::LateUpdate(void)
{
}

void COakMonster::Release(void)
{
}


