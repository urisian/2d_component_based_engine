#include "stdafx.h"
#include "FontManager.h"
#include "GraphicsManager.h"
CFontManager* CFontManager::m_s_pInstance = nullptr;

CFontManager * CFontManager::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CFontManager;
	return m_s_pInstance;
}

void CFontManager::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CFontManager::Initialize(void)
{
	AddFontResourceEx(L"..\\Resource\\Font\\SohoGothicProMedium.ttf", FR_PRIVATE, 0);
	int a = 0;
	if (FAILED(D3DXCreateFont(CGraphicsManager::GetInstance()->GetDevice(), -15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"SohoGothicProMedium", &m_pFont)))
		a = 3;

}

void CFontManager::Update(void)
{
}

void CFontManager::LateUpdate(void)
{
}

void CFontManager::Release(void)
{
	for (auto& text : m_mTextList)
		delete text.second;

	m_mTextList.clear();
}

void CFontManager::AddText(std::string textKey, std::string msg, D3DXVECTOR3 position, D3DXCOLOR color)
{
	Text* pNewText = new Text;

	pNewText->m_message = msg;
	pNewText->m_isVisible = true;
	pNewText->m_position = position;
	pNewText->m_color = color;

	m_mTextList[textKey] = pNewText;
}

void CFontManager::RewriteText(std::string textKey, std::string msg)
{
	m_mTextList[textKey]->m_message = msg;
}

void CFontManager::DeleteText(std::string textKey)
{
	auto& it = m_mTextList.find(textKey);
	delete (*it).second;
	m_mTextList.erase(it);
}

void CFontManager::DrawMyText(Text * pText)
{
	if (!m_pFont)
		return;

	DWORD format = DT_EXPANDTABS;
	format |= DT_RIGHT;

	std::basic_string<WCHAR> msg = StrToWStr(pText->m_message).c_str();

	RECT rect = { int(pText->m_position.x), int(pText->m_position.y), int(pText->m_position.x + 50), int(pText->m_position.y + 50) };
    m_pFont->DrawText( NULL, msg.c_str(), -1, &rect, format, pText->m_color);
}

CFontManager::CFontManager()
{
}


CFontManager::~CFontManager()
{
	Release();
}
