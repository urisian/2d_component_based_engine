#include "stdafx.h"
#include "Texture.h"
#include "GraphicsManager.h"

CTexture::CTexture()
{
}


CTexture::~CTexture()
{
}

bool CTexture::InsertTexInfo(const std::string & fullPath)
{
	std::string stateKey = GetStateKey(fullPath);


	TEXINFO* pTexInfo = new TEXINFO;
	if (FAILED(D3DXGetImageInfoFromFile(StrToWStr(fullPath).c_str(), &pTexInfo->tImageInfo)))
	{
		MessageBox(nullptr, L"GetImageInfo Failed in InsertTexInfo", L"Texture.cpp", MB_OK);
		return false;
	}
	if (FAILED(D3DXCreateTextureFromFileEx(CGraphicsManager::GetInstance()->GetDevice(),
										   StrToWStr(fullPath).c_str(),
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
		MessageBox(nullptr, L"CreateTextureFromFile Failed in InsertTexInfo", L"Texture.cpp", MB_OK);
		return false;
	}
	m_mTexInfo[stateKey].emplace_back(pTexInfo);

	return true;
}

std::vector<TEXINFO*>& CTexture::GetTexInfos(const std::string& stateKey)
{
	std::vector<TEXINFO*> a = m_mTexInfo[stateKey];
	return m_mTexInfo[stateKey];
}

std::string CTexture::GetStateKey(const std::string & fullPath)
{
	size_t startPoint, endPoint;
	startPoint = fullPath.find_first_of("\\");
	startPoint = fullPath.find("\\", ++startPoint);
	startPoint = fullPath.find("\\", ++startPoint);
	startPoint = fullPath.find("\\", ++startPoint);
	startPoint = fullPath.find("\\", ++startPoint);
	endPoint = fullPath.find_last_of(".");

	std::string stateKey = fullPath.substr(++startPoint, endPoint - startPoint);

	while (isdigit(stateKey.back()))
		stateKey.pop_back();

	return stateKey;
}
