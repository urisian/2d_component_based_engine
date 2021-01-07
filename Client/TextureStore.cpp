#include "stdafx.h"
#include "TextureStore.h"
#include "Texture.h"

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


			CreateTexture(fullFilePath);
		} while (FindNextFile(findHandle, &fileData));
	} while (!dirNameVector.empty());
}

void CTextureStore::Release(void)
{
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
	std::string stateKey	= GetStateKey(fullPath);

	std::map<std::string, CTexture*>* pCurMap = nullptr;

	if (sectionKey == "BACKGROUND")
		pCurMap = &m_mTexture[TEXID::BACKGROUND];
	else if (sectionKey == "BUTTON")
		pCurMap = &m_mTexture[TEXID::BUTTON];
	else if (sectionKey == "DECORATION")
		pCurMap = &m_mTexture[TEXID::DECORATION];
	else if (sectionKey == "MONSTER")
		pCurMap = &m_mTexture[TEXID::MONSTER];
	else if (sectionKey == "PROJECTILE")
		pCurMap = &m_mTexture[TEXID::PROJECTILE];
	else if (sectionKey == "TURRET")
		pCurMap = &m_mTexture[TEXID::TURRET];
	else if (sectionKey == "UI")
		pCurMap = &m_mTexture[TEXID::UI];
	else if (sectionKey == "UNIT")
		pCurMap = &m_mTexture[TEXID::UNIT];
	else
		MessageBox(nullptr, L"Need to set right map for sectionKey in CreateTexture", L"CTextureStore", MB_OK);

	CTexture* pNewTexture = new CTexture;
	(*pCurMap)[objectKey] = pNewTexture;
	pNewTexture;
	return false;
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

std::string CTextureStore::GetStateKey(const std::string & fullPath)
{
	size_t startPoint, endPoint;
	startPoint	= fullPath.find_first_of("\\");
	startPoint	= fullPath.find("\\", ++startPoint);
	startPoint	= fullPath.find("\\", ++startPoint);
	startPoint	= fullPath.find("\\", ++startPoint);
	endPoint	= fullPath.find_last_of(".");
	
	std::string stateKey = fullPath.substr(++startPoint, endPoint - startPoint);
	
	while (isdigit(stateKey.back()))
		stateKey.pop_back();

	return fullPath.substr(++startPoint, endPoint - startPoint);
}
