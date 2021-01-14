#include "stdafx.h"
#include "Animation.h"
#include "GraphicsComponent.h"
#include "DataStore.h"
#include "Texture.h"

CAnimation::CAnimation(CGraphicsComponent* pOwner)
{
	m_pOwner	= pOwner;
	m_status	= ANIMATION::STATUS::PLAY;

	m_aniSecPerFrame	= 0.f;
	m_curIndex			= 0.f;
	m_maxIndex			= 0;

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


	m_maxIndex = m_pOwner->GetCTexture()->GetTexInfos(pOwnerObject->GetStateKey()).size();
}

void CAnimation::Update(void)
{
	if (m_status == ANIMATION::STATUS::STOP)
		m_curIndex = 0;
	else if (m_status == ANIMATION::STATUS::PLAY)
	{
		m_curIndex += m_aniSecPerFrame;
		if (m_curIndex > m_maxIndex)
			m_curIndex -= (float)m_maxIndex;
	}
}

void CAnimation::LateUpdate(void)
{
}

void CAnimation::Release(void)
{
}
