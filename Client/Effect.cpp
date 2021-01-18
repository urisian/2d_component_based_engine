#include "stdafx.h"
#include "Effect.h"
#include "GraphicsComponent.h"
#include "FRC.h"
#include "Animation.h"

CEffect::CEffect(std::string objectKey, std::string stateKey, CObject* pParent, int repeat, bool killOwner)
{
	m_pParent = pParent;
	m_objectKey = objectKey;
	m_stateKey = stateKey;
	m_repeat = repeat;
	m_killOwner = killOwner;

	m_timer = 0;
	m_lifeTime = 0;
	Initialize();
}


CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize(void)
{
	m_objID = OBJID::EFFECT;
	m_dataID = DATAID::EFFECT;

	__super::Initialize();

}

void CEffect::Update(void)
{
	__super::Update();
	CGraphicsComponent* pGC = GetComponent<CGraphicsComponent>();

	if (pGC->GetAnimation() != nullptr)
	{
		m_lifeTime = 1 / pGC->GetAnimation()->GetAniSecPerFrame() * pGC->GetAnimation()->GetMaxIndex();

		m_timer += GET_DT();

		if (m_timer >= m_lifeTime)
		{
			if (m_repeat == 0)
				m_needToBeDeleted = true;
			else
			{
				--m_repeat;
				m_timer = 0;
			}
		}
	}
}

void CEffect::LateUpdate(void)
{
	__super::LateUpdate();
}

void CEffect::Release(void)
{
	if (m_killOwner)
		m_pParent->SetNeedToBeDeleted(true);
}

void CEffect::AddChildAndComponents(void)
{
	AddComponent<CGraphicsComponent>();
}

void CEffect::InitializeComponents(void)
{
}
