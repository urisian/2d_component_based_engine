#include "stdafx.h"
#include "Texture_Manager.h"
#include "Single_Texture.h"
#include "MultiTexture.h"
CTexture_Manager* CTexture_Manager::m_pInstance = nullptr; 
CTexture_Manager::CTexture_Manager()
{
}


CTexture_Manager::~CTexture_Manager()
{
	Release_Texture_Manager(); 
}

const TEXINFO * CTexture_Manager::Get_TexInfo(const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & iIndex)
{
	auto& iter_Find = m_mapTexture.find(wstrObjectKey);
	if (m_mapTexture.end() == iter_Find)
		return nullptr;

	return iter_Find->second->Get_TexInfo(wstrStateKey, iIndex);
}

HRESULT CTexture_Manager::Insert_Texture_Manager(TEX_ID eTexID, const wstring & wstrFilePath, const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & iIndex)
{
	auto& iter_Find = m_mapTexture.find(wstrObjectKey);
	// 이때는 어떤 상황? - 제일 처음 집어넣ㄴ느 그런 상황. 
	CTexture* pTexture = nullptr; 
	if (m_mapTexture.end() == iter_Find)
	{
		switch (eTexID)
		{
		case CTexture_Manager::MULTI_TEX:
			pTexture = new CMultiTexture;
			break;
		case CTexture_Manager::SINGLE_TEX:
			pTexture = new CSingle_Texture;
			break;
		default:
			break;
		}
		if (FAILED(pTexture->Insert_Texture(wstrFilePath,wstrStateKey, iIndex )))
		{
			ERR_MSG(L"TextureManager Insert Faield"); 
			return E_FAIL; 
		}
		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else if (eTexID == MULTI_TEX)
	{
		if (FAILED(m_mapTexture[wstrObjectKey]->Insert_Texture(wstrFilePath, wstrStateKey, iIndex)))
		{
			ERR_MSG(L"TextureManager MultiTexture Insert Faield");
			return E_FAIL; 
		}
	}
	return S_OK;
}

void CTexture_Manager::Release_Texture_Manager()
{
	for (auto& rPair : m_mapTexture)
		Safe_Delete(rPair.second);

	m_mapTexture.clear(); 
// 	for_each(m_mapTexture.begin(), m_mapTexture.end(), [](auto& rPair) 
// 	{
// 		if (rPair.second)
// 		{
// 			delete rPair.second; 
// 			rPair.second = nullptr; 
// 		}
// 	});
}
