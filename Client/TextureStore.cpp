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
	//���丮�� �����̸��� ������ ����
	std::vector<std::string> dirNameVector;
	std::vector<std::string> fileNameVector;

	//���� �����͸� ���� ����
	WIN32_FIND_DATA fileData;


	//���� �����ִ� ����, ���丮, �׸��� ��ü �н�
	std::string curFile;
	std::string curDir;
	std::string fullFilePath;

	//������� �־��ش�.
	dirNameVector.push_back(m_resourcePath);

	do
	{
		//���� ���丮�� ���Ϳ��� ������ �Է� �� ���ʹ� pop.back()���� �Է����� ���� ����.
		curDir = dirNameVector.back();
		dirNameVector.pop_back();

		//���� ���丮�� ù���� ������ ã�� fileData�� ������ �ְ� HANDLE�� ��ȯ
		HANDLE findHandle = FindFirstFile(StrToWStr(curDir + "\\*").c_str(), &fileData);

		//���丮�� �߸��Ǿ��ٸ� ���⼭ ������.
		if (findHandle == INVALID_HANDLE_VALUE)
		{
			MessageBox(nullptr, L"Given path is wrong during getting handle", L"CDataStore", MB_OK);
			return;
		}

		do
		{
			//ã�� fileData�κ��� ���� �����ִ� ����, �׸��� Ǯ �н��� ����
			curFile = WStrToStr(fileData.cFileName);
			fullFilePath = curDir + "\\" + curFile;

			//���� �����ִ� ������ directory���� �ƴ��� üũ
			bool isItDir = ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) ? false : true;


			//���� �̸��� .���� �����ϸ� �ý��� �����̴�, �ѱ�.
			if (curFile[0] == '.')
				continue;

			//���丮��� ���丮 ���Ϳ� �ְ� �ѱ��.
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

