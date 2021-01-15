#include "stdafx.h"
#include "ClickableComponent.h"
#include "InputManager.h"
#include "CollisionHelper.h"
#include "Debugger.h"
#include "Object.h"
#include "CollisionManager.h"
#include "DataStore.h"

CClickableComponent::CClickableComponent(CObject* pOwner) : CComponent(pOwner)
{
	m_mouseOver = false;
	m_clickDown = false;
	m_clickUp	= false;

	m_cOrder	= 0;
}


CClickableComponent::~CClickableComponent()
{
}

void CClickableComponent::Initialize(void)
{
	__super::Initialize();

	GET_VALUE(m_pOwner->GetDataID(), m_pOwner->GetObjectKey(), "m_cOrder", m_cOrder);
	CCollisionManager::GetInstance()->AddClickableComponent(this);
}

void CClickableComponent::Update(void)
{
	__super::Update();

	CheckMouseOver();
	CheckClickUp();
	CheckClickDown();

	if (m_clickUp)
		m_fpPlay();
}

void CClickableComponent::LateUpdate(void)
{
}

void CClickableComponent::Release(void)
{
}

void CClickableComponent::StateChangeInit(void)
{
}


void CClickableComponent::SetPlayFunc(std::function<void(void)> funcPointer)
{
	m_fpPlay = funcPointer;
}

void CClickableComponent::CheckMouseOver(void)
{
	if (CollisionHelper::PointRectCollision(GET_MOUSE_POS(), m_pOwner))
		m_mouseOver = true;
	else
		m_mouseOver = false;
}

void CClickableComponent::CheckClickDown(void)
{
	if (m_mouseOver && IMKEY_PRESS(MOUSE_LEFT))
		m_clickDown = true;
	else
		m_clickDown = false;
}

void CClickableComponent::CheckClickUp(void)
{
	if (m_clickDown && IMKEY_UP(MOUSE_LEFT))
		m_clickUp = true;
	else
		m_clickUp = false;
}
