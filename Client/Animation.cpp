#include "stdafx.h"
#include "Animation.h"
#include "GraphicsComponent.h"
#include "DataStore.h"
#include "Texture.h"
#include "FRC.h"

CAnimation::CAnimation(CGraphicsComponent* pOwner)
{
	m_pOwner	= pOwner;
	m_status	= ANIMATION::STATUS::PLAY;

	m_aniSecPerFrame	= 0.f;
	m_lastFrameIndex	= 0;
	m_curIndex			= 0.f;
	m_maxIndex			= 0;

	m_repeat			= true;
	Initialize();
}


CAnimation::~CAnimation()
{
}

void CAnimation::Initialize(void)
{
	CObject* pOwnerObject = m_pOwner->GetOwner();

	GET_VALUE(pOwnerObject->GetDataID(), pOwnerObject->GetObjectKey(), pOwnerObject->GetStateKey() 
				+ "_m_aniSecPerFrame", m_aniSecPerFrame);

	m_curIndex = 0;
	m_maxIndex = m_pOwner->GetCTexture()->GetTexInfos(pOwnerObject->GetStateKey()).size();
}

void CAnimation::Update(void)
{
	
}

void CAnimation::LateUpdate(void)
{
	if (m_status == ANIMATION::STATUS::STOP)
		m_curIndex = 0;
	else if (m_status == ANIMATION::STATUS::PLAY)
	{
		m_lastFrameIndex = (int)m_curIndex;
		m_curIndex += m_aniSecPerFrame * GET_DT();
		if (m_curIndex >= m_maxIndex)
		{
			if (m_repeat)
				m_curIndex -= (float)m_maxIndex;
			else
			{
				m_aniSecPerFrame = 0.f;
				m_curIndex = (float)m_maxIndex - 1;
			}
		}
	}
	else if (m_status == ANIMATION::STATUS::PAUSE)
		return;
}

void CAnimation::Release(void)
{
}

void CAnimation::StateChangeInit(void)
{
	int curMaxIndex = m_maxIndex;
	float curAniSecPerFrame = m_aniSecPerFrame;

	CObject* pOwnerObject = m_pOwner->GetOwner();

	GET_VALUE(pOwnerObject->GetDataID(), pOwnerObject->GetObjectKey(), 
			  pOwnerObject->GetStateKey() + "_m_aniSecPerFrame", m_aniSecPerFrame);

	m_maxIndex = m_pOwner->GetCTexture()->GetTexInfos(pOwnerObject->GetStateKey()).size();

	if (m_aniSecPerFrame != curAniSecPerFrame || curMaxIndex != m_maxIndex)
		m_curIndex = 0;
}

