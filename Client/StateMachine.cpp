#include "stdafx.h"
#include "StateMachine.h"


#include "ObjectState.h"

CStateMachine::CStateMachine(CObject* pOwner)
{
	m_pOwner = pOwner;
}


CStateMachine::~CStateMachine()
{
}

void CStateMachine::Initialize(void)
{
}

void CStateMachine::Update(void)
{
	if (m_pPrevState)
	{
		m_pPrevState->OnExit();
		m_pPrevState = nullptr;
	}

	if(m_pCurState)
		m_pCurState->OnUpdate();

	if (m_pNextState && (m_pNextState != m_pCurState))
	{
		m_pNextState->OnStart();
		m_pPrevState = m_pCurState;
		m_pCurState = m_pNextState;
		m_pNextState = nullptr;
	}
}

void CStateMachine::LateUpdate(void)
{
}

void CStateMachine::Release(void)
{
}
