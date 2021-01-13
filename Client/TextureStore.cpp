#include "stdafx.h"
#include "TextureStore.h"
#include "Texture.h"
#include "GraphicsManager.h"

CTextureStore* CTextureStore::m_s_pInstance = nullptr;

CTextureStore * CTextureStore::GetInstance(void)
{
	if (m_s_pInstance == nullptr)
		m_s_pInstance = new CTextureStore;
	
	return m_s_pInstance;
}

void CTextureStore::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CTextureStore::Initialize(void)
{
	//디렉토리와 파일이름을 저장할 벡터
	std::vector<std::string> dirNameVector;
	std::vector<std::string> fileNameVector;

	//파일 데이터를 받을 변수
	WIN32_FIND_DATA fileData;


	//현재 보고있는 파일, 디렉토리, 그리고 전체 패스
	std::string curFile;
	std::string curDir;
	std::string fullFilePath;

	//출발점을 넣어준다.
	dirNameVector.push_back(m_resourcePath);

	do
	{
		//현재 디렉토리를 벡터에서 꺼내어 입력 후 벡터는 pop.back()으로 입력해준 것을 제거.
		curDir = dirNameVector.back();
		dirNameVector.pop_back();

		//받은 디렉토리의 첫번쨰 파일을 찾아 fileData에 정보를 넣고 HANDLE을 반환
		HANDLE findHandle = FindFirstFile(StrToWStr(curDir + "\\*").c_str(), &fileData);

		//디렉토리가 잘못되었다면 여기서 터진다.
		if (findHandle == INVALID_HANDLE_VALUE)
		{
			MessageBox(nullptr, L"Given path is wrong during getting handle", L"CDataStore", MB_OK);
			return;
		}

		do
		{
			//찾은 fileData로부터 현재 보고있는 파일, 그리고 풀 패스를 설정
			curFile = WStrToStr(fileData.cFileName);
			fullFilePath = curDir + "\\" + curFile;

			//현재 보고있는 파일이 directory인지 아닌지 체크
			bool isItDir = ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) ? false : true;


			//파일 이름이 .으로 시작하면 시스템 파일이다, 넘김.
			if (curFile[0] == '.')
				continue;

			//디렉토리라면 디렉토리 벡터에 넣고 넘긴다.
			if (isItDir)
			{
				dirNameVector.push_back(fullFilePath);
				continue;
			}


			if (!CreateTexture(fullFilePath))
			{
				MessageBox(nullptr, StrToWStr(fullFilePath).c_str(), L"CDataStore", MB_OK);
				return;
			}
		} while (FindNextFile(findHandle, &fileData));
	} while (!dirNameVector.empty());
}

void CTextureStore::Release(void)
{
}

CTexture * CTextureStore::GetTexture(OBJID::ID OBJID, std::string objectKey)
{
	CTexture* pCTexture = m_mTexture[OBJID][objectKey];
#if _DEBUG
	if (pCTexture == nullptr)
		MessageBox(nullptr, StrToWStr(objectKey + " missing texture in GetTexture function").c_str(), L"TextureStore.cpp", MB_OK);
#endif
	return m_mTexture[OBJID][objectKey];
}

CTextureStore::CTextureStore(void)
{
	m_resourcePath = "..\\Resource\\Texture";
}


CTextureStore::~CTextureStore(void)
{
	Release();
}

bool CTextureStore::CreateTexture(const std::string& fullPath)
{
	std::string sectionKey	= GetSectionKey(fullPath);
	std::string objectKey	= GetObjectKey(fullPath);

	std::map<std::string, CTexture*>* pCurMap = nullptr;

	if (sectionKey == "BUTTON")
		pCurMap = &m_mTexture[OBJID::BUTTON];
	else if (sectionKey == "DECORATION")
		pCurMap = &m_mTexture[OBJID::DECORATION];
	else if (sectionKey == "MONSTER")
		pCurMap = &m_mTexture[OBJID::MONSTER];
	else if (sectionKey == "PROJECTILE")
		pCurMap = &m_mTexture[OBJID::PROJECTILE];
	else if (sectionKey == "TURRET")
		pCurMap = &m_mTexture[OBJID::TURRET];
	else if (sectionKey == "UI")
		pCurMap = &m_mTexture[OBJID::UI];
	else if (sectionKey == "UNIT")
		pCurMap = &m_mTexture[OBJID::UNIT];
	else
		MessageBox(nullptr, L"Need to set right map for sectionKey in CreateTexture", L"CTextureStore", MB_OK);

	
	auto& it = pCurMap->find(objectKey);
	if (it == pCurMap->end())
	{
		CTexture* pNewTexture = new CTexture;
		(*pCurMap)[objectKey] = pNewTexture;
	}
	
	


	return (*pCurMap)[objectKey]->InsertTexInfo(fullPath);;
}

std::string CTextureStore::GetSectionKey(const std::string & fullPath)
{
	size_t startPoint, endPoint;
	startPoint	= fullPath.find_first_of("\\");
	startPoint	= fullPath.find("\\", ++startPoint);
	startPoint	= fullPath.find("\\", ++startPoint);
	endPoint	= fullPath.find("\\", ++startPoint);

	return fullPath.substr(startPoint, endPoint - startPoint);
}

std::string CTextureStore::GetObjectKey(const std::string & fullPath)
{
	size_t startPoint, endPoint;
	startPoint	= fullPath.find_first_of("\\");
	startPoint	= fullPath.find("\\", ++startPoint);
	startPoint	= fullPath.find("\\", ++startPoint);
	startPoint	= fullPath.find("\\", ++startPoint);
	endPoint	= fullPath.find("\\", ++startPoint);
	
	return fullPath.substr(startPoint, endPoint - startPoint);
}

