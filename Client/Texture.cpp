#include "stdafx.h"
#include "Texture.h"


CTexture::CTexture()
{
}


CTexture::~CTexture()
{
}

bool CTexture::InsertTexInfo(const std::string & fullPath)
{
	std::string stateKey = GetStateKey(fullPath);

	auto& iter = m_mTexInfo.find(stateKey);

	if (iter == m_mTexInfo.end())
	{

	}

	TEXINFO* pTexInfo = new TEXINFO;
	if (FAILED(D3DXGetImageInfoFromFile(StrToWStr(fullPath).c_str(), &pTexInfo->tImageInfo)))
	{
		MessageBox(nullptr, L"GetImageInfo Failed in InsertTexInfo", L"Texture.cpp", MB_OK);
		return false;
	}

	return false;
}

std::string CTexture::GetStateKey(const std::string & fullPath)
{
	size_t startPoint, endPoint;
	startPoint = fullPath.find_first_of("\\");
	startPoint = fullPath.find("\\", ++startPoint);
	startPoint = fullPath.find("\\", ++startPoint);
	startPoint = fullPath.find("\\", ++startPoint);
	endPoint = fullPath.find_last_of(".");

	std::string stateKey = fullPath.substr(++startPoint, endPoint - startPoint);

	while (isdigit(stateKey.back()))
		stateKey.pop_back();

	return fullPath.substr(++startPoint, endPoint - startPoint);
}
