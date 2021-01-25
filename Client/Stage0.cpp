#include "stdafx.h"
#include "Stage0.h"
#include "DataStore.h"
#include "GraphicsComponent.h"
#include "BaseTurret.h"
#include "TurretRing.h"
#include "Wave.h"
#include "FontManager.h"
#include "UserInterface.h"
#include "Decoration.h"
#include "Application.h"
#include "GameInfo.h"
#include "Animation.h"
#include "FireRain.h"
#include "Reinforce.h"

CStage0::CStage0()
{
}


CStage0::~CStage0()
{
}

void CStage0::Initialize(void)
{
	__super::Initialize();

	CGameInfo::GetInstance()->SetLife(20);
	CGameInfo::GetInstance()->SetGold(420);

	CFontManager::GetInstance()->AddText("Life", std::to_string(CGameInfo::GetInstance()->GetLife()), D3DXVECTOR3(5, 21, 0), D3DXCOLOR(0.7, 0.6, 0.4, 1.0));
	CFontManager::GetInstance()->AddText("Gold", std::to_string(CGameInfo::GetInstance()->GetGold()), D3DXVECTOR3(75, 21, 0), D3DXCOLOR(0.7, 0.6, 0.4, 1.0));
	CFontManager::GetInstance()->AddText("NumOfWave", std::to_string(m_curWaveNum) + " / " + std::to_string(m_vWave.size()), D3DXVECTOR3(45, 43, 0), D3DXCOLOR(0.7, 0.6, 0.4, 1.0));

	CDecoration* pDecoration = new CDecoration("BlackBoard");
	pDecoration->SetPosition(D3DXVECTOR3(CApplication::GetInstance()->GetWndWidth()/2.f * (-0.88), CApplication::GetInstance()->GetWndHeight()/2.f * 0.9f, 0));
	pDecoration->AddChildAndComponents();

	pDecoration = new CDecoration("BlackBoard");
	pDecoration->SetPosition(D3DXVECTOR3(CApplication::GetInstance()->GetWndWidth() / 2.f * (-0.72), CApplication::GetInstance()->GetWndHeight() / 2.f * 0.9f, 0));
	pDecoration->GetSize().x += 30;
	pDecoration->AddChildAndComponents();

	pDecoration = new CDecoration("BlackBoard");
	pDecoration->SetPosition(D3DXVECTOR3(CApplication::GetInstance()->GetWndWidth() / 2.f * (-0.79), CApplication::GetInstance()->GetWndHeight() / 2.f * 0.83f, 0));
	pDecoration->GetSize().x += 80;
	pDecoration->AddChildAndComponents();

	pDecoration = new CDecoration("LifeUI");
	pDecoration->SetPosition(D3DXVECTOR3(CApplication::GetInstance()->GetWndWidth() / 2.f * (-0.95), CApplication::GetInstance()->GetWndHeight() / 2.f * 0.9f, 0));
	pDecoration->AddChildAndComponents();

	pDecoration = new CDecoration("GoldUI");
	pDecoration->SetPosition(D3DXVECTOR3(CApplication::GetInstance()->GetWndWidth() / 2.f * (-0.78), CApplication::GetInstance()->GetWndHeight() / 2.f * 0.9f, 0));
	pDecoration->AddChildAndComponents();

	pDecoration = new CDecoration("WaveUI");
	pDecoration->SetPosition(D3DXVECTOR3(CApplication::GetInstance()->GetWndWidth() / 2.f * (-0.95), CApplication::GetInstance()->GetWndHeight() / 2.f * 0.83f, 0));
	pDecoration->AddChildAndComponents();

	pDecoration = new CDecoration("SkillFrame");
	pDecoration->SetPosition(D3DXVECTOR3(CApplication::GetInstance()->GetWndWidth() / 2.f * (-0.88), CApplication::GetInstance()->GetWndHeight() / 2.f * (-0.88f), 0));
	pDecoration->AddChildAndComponents();
	pDecoration->GetComponent<CGraphicsComponent>()->GetAnimation()->SetRepeat(false);

	pDecoration = new CDecoration("SkillFrame");
	pDecoration->SetPosition(D3DXVECTOR3(CApplication::GetInstance()->GetWndWidth() / 2.f * (-0.70), CApplication::GetInstance()->GetWndHeight() / 2.f * (-0.88f), 0));
	pDecoration->AddChildAndComponents();
	pDecoration->GetComponent<CGraphicsComponent>()->GetAnimation()->SetRepeat(false);

	CUserInterface* pUI = new CFireRain;
	pUI->SetPosition(D3DXVECTOR3(CApplication::GetInstance()->GetWndWidth() / 2.f * (-0.70), CApplication::GetInstance()->GetWndHeight() / 2.f * (-0.86f), 0));
	pUI->AddChildAndComponents();

	pUI = new CReinforce;
	pUI->SetPosition(D3DXVECTOR3(CApplication::GetInstance()->GetWndWidth() / 2.f * (-0.88), CApplication::GetInstance()->GetWndHeight() / 2.f * (-0.86f), 0));
	pUI->AddChildAndComponents();

}

void CStage0::Update(void)
{
	__super::Update();
	CFontManager::GetInstance()->RewriteText("Life", std::to_string(CGameInfo::GetInstance()->GetLife()));
	CFontManager::GetInstance()->RewriteText("Gold", std::to_string(CGameInfo::GetInstance()->GetGold()));
	CFontManager::GetInstance()->RewriteText("NumOfWave", std::to_string(m_curWaveNum) + " / " + std::to_string(m_vWave.size()));
	
}

void CStage0::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CStage0::Release(void)
{
}

void CStage0::SpawnWave(void)
{
}
