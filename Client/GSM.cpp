#include "stdafx.h"
#include "GSM.h"
#include "GameState.h"
#include "Stage0.h"

CGSM* CGSM::m_s_pInstance = nullptr;

CGSM * CGSM::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CGSM;
	return m_s_pInstance;
}

void CGSM::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CGSM::Initialize(void)
{
	CGameState* pCurState = new CStage0;
	m_pNextState = pCurState;
}

void CGSM::Update(void)
{
	if (m_pNextState != nullptr)
	{
		if (m_needToBeClean)
		{
			while (m_sStateStack.size() != 0)
			{
				SAFE_DELETE(m_sStateStack.top());
				m_sStateStack.pop();
			}
			m_needToBeClean = false;	
		}
		else if(m_pCurState)
		{
			m_pCurState->SetActivated(false);
		}
		m_sStateStack.push(m_pNextState);
		m_pCurState = m_pNextState;
		m_pNextState = nullptr;
		m_pCurState->Initialize();
	}

	m_pCurState->Update();
}

void CGSM::LateUpdate(void)
{
	m_pCurState->LateUpdate();
}

void CGSM::Release(void)
{
}

CGSM::CGSM(void)
{
	m_needToBeClean		= false;

	m_pCurState			= nullptr;
	m_pNextState		= nullptr;
}


CGSM::~CGSM(void)
{
	Release();
}
