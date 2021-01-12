#include "stdafx.h"
#include "ClickableComponent.h"
#include "InputManager.h"
#include "CollisionHelper.h"
#include "Debugger.h"
#include "Object.h"

CClickableComponent::CClickableComponent(void)
{
	m_mouseOver = false;
	m_clickDown = false;
	m_clickUp	= false;
}


CClickableComponent::~CClickableComponent()
{
}

void CClickableComponent::Initialize(void)
{
}

void CClickableComponent::Update(void)
{
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
