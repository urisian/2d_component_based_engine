#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release_Texture();
}

const TEXINFO * CMultiTexture::Get_TexInfo(const wstring & wstrStateKey /*= L""*/, const int & iIndex/* = 0*/)
{
	auto& iter_Find = m_mapTexture.find(wstrStateKey); 
	if (m_mapTexture.end() == iter_Find)
		return nullptr;
	return iter_Find->second[iIndex]; 

	//return m_mapTexture[wstrStateKey][iIndex];
}
// ../Texture/Stage/Terrain/Tile/Tile%d.png
HRESULT CMultiTexture::Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey /*= L""*/, const int & iIndex /*= 0*/)
{
	auto& iter_Find = m_mapTexture.find(wstrStateKey); 
	if (iter_Find != m_mapTexture.end())
		return E_FAIL; 

	TCHAR szBuf[MAX_PATH] = L"";
	TEXINFO* pTexInfo = nullptr; 
	for (int i = 0 ; i < iIndex; ++i)
	{
		swprintf_s(szBuf, wstrFilePath.c_str(), i);
		pTexInfo = new TEXINFO;
		if (FAILED(D3DXGetImageInfoFromFile(szBuf, &pTexInfo->tImageInfo)))
		{
			ERR_MSG(L"Loading Image Info Failed");
			return E_FAIL;
		}
		if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
			szBuf,
			pTexInfo->tImageInfo.Width,
			pTexInfo->tImageInfo.Height,
			pTexInfo->tImageInfo.MipLevels,
			0,
			pTexInfo->tImageInfo.Format,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			nullptr,
			nullptr,
			&pTexInfo->pTexture)))
		{
			wstring wstrErr = wstrFilePath + L"Loading Failed";
			ERR_MSG(wstrErr.c_str());
			return E_FAIL;
		}
		m_mapTexture[wstrStateKey].emplace_back(pTexInfo); 
	}
	return S_OK;
}

void CMultiTexture::Release_Texture()
{
	for (auto& rPair : m_mapTexture)
	{
		for (auto& rTexInfo : rPair.second)
		{
			Safe_Delete(rTexInfo);
		}
		rPair.second.clear(); 
		// �ƴ�.. �ֵ��.. ���� �ƴ���... 
		//rPair.second.swap(vector<TEXINFO*>()); 
		rPair.second.shrink_to_fit(); 
	}
}
