#include "stdafx.h"
#include "DataStore.h"

CDataStore* CDataStore::m_s_pInstance = nullptr;

CDataStore * CDataStore::GetInstance(void)
{
	if(!m_s_pInstance)
		m_s_pInstance = new CDataStore;

	return m_s_pInstance;
}

void CDataStore::DestroyInstance(void)
{
	SAFE_DELETE(m_s_pInstance);
}

void CDataStore::Initialize(void)
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
		HANDLE findHandle = FindFirstFile(StrToWStr(curDir + "\\*").c_str() , &fileData);

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
			bool isItDir = ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)? false : true;


			//파일 이름이 .으로 시작하면 시스템 파일이다, 넘김.
			if (curFile[0] == '.')
				continue;

			//디렉토리라면 디렉토리 벡터에 넣고 넘긴다.
			if (isItDir)
			{
				dirNameVector.push_back(fullFilePath);
				continue;
			}



			ReadFile(fullFilePath);

		} while (FindNextFile(findHandle, &fileData));
	} while (!dirNameVector.empty());
}


CDataStore::CDataStore(void)
{
	m_resourcePath = "..\\Resource\\Data";
}


CDataStore::~CDataStore(void)
{
	Release();
}

void CDataStore::ReadFile(const std::string & fullPath)
{
	std::ifstream readFile;
	readFile.open(fullPath.c_str());

	if (readFile.is_open())
	{
		std::string line;
		std::string sectionKey	= GetSectionKey(fullPath);
		std::string objectKey	= GetObjectKey(fullPath);
		std::string variableKey;
		std::string keyValue;

		std::map<std::string, std::map<std::string, std::string>>* pCurMap = nullptr;

		if (sectionKey == "BACKGROUND")
			pCurMap = &m_mDataMap[DATAID::BACKGROUND];
		else if (sectionKey == "ANIMATION")
			pCurMap = &m_mDataMap[DATAID::ANIMATION];
		else if (sectionKey == "BUTTON")
			pCurMap = &m_mDataMap[DATAID::BUTTON];
		else if (sectionKey == "DECORATION")
			pCurMap = &m_mDataMap[DATAID::DECORATION];
		else if (sectionKey == "ENGINE")
			pCurMap = &m_mDataMap[DATAID::ENGINE];
		else if (sectionKey == "MONSTER")
			pCurMap = &m_mDataMap[DATAID::MONSTER];
		else if (sectionKey == "STAGE")
			pCurMap = &m_mDataMap[DATAID::STAGE];
		else if (sectionKey == "TURRET")
			pCurMap = &m_mDataMap[DATAID::TURRET];
		else if (sectionKey == "UI")
			pCurMap = &m_mDataMap[DATAID::UI];
		else if (sectionKey == "UNIT")
			pCurMap = &m_mDataMap[DATAID::UNIT];
		else
			MessageBox(nullptr, L"Need to set right map for sectionKey in ReadFile", L"CDataStore", MB_OK);

		while (!readFile.eof() && std::getline(readFile, line))
		{
			variableKey = GetVariableKey(line);
			keyValue = GetKeyValue(line);

			(*pCurMap)[objectKey][variableKey] = keyValue;
		}

	}

}



std::string CDataStore::GetSectionKey(const std::string & fullPath)
{
	size_t startPoint, endPoint;
	startPoint	= fullPath.find_first_of("\\");
	startPoint	= fullPath.find("\\", ++startPoint);
	startPoint	= fullPath.find("\\", ++startPoint);
	endPoint	= fullPath.find("\\", ++startPoint);

	return fullPath.substr(startPoint, endPoint - startPoint);
}

std::string CDataStore::GetObjectKey(const std::string & fullPath)
{
	size_t startPoint, endPoint;
	startPoint	= fullPath.find_first_of("\\");
	startPoint	= fullPath.find("\\", ++startPoint);
	startPoint	= fullPath.find("\\", ++startPoint);
	startPoint	= fullPath.find("\\", ++startPoint);
	endPoint	= fullPath.find_last_of(".");
	
	return fullPath.substr(++startPoint, endPoint - startPoint);
}

std::string CDataStore::GetVariableKey(const std::string & lineFromFile)
{
	size_t endPoint = lineFromFile.find_first_of("=");

	return lineFromFile.substr(0, endPoint);
}

std::string CDataStore::GetKeyValue(const std::string & lineFromFile)
{
	size_t startPoint = lineFromFile.find_first_of("=");
	return lineFromFile.substr(++startPoint);
}

void CDataStore::Release(void)
{
}


std::stringstream & operator >> (std::stringstream & in, D3DXVECTOR3 & d3dVec3)
{
	std::string vecStr;
	std::string vecStrX, vecStrY, vecStrZ;

	in >> vecStr;

	size_t xEndPos, yEndPos;

	xEndPos = vecStr.find_first_of(",");
	yEndPos = vecStr.find_last_of(",");

	vecStrX = vecStr.substr(0, xEndPos);
	vecStrY = vecStr.substr(++xEndPos, yEndPos - xEndPos);
	vecStrZ = vecStr.substr(++yEndPos);

	std::stringstream ssX(vecStrX);
	std::stringstream ssY(vecStrY);
	std::stringstream ssZ(vecStrZ);

	ssX >> d3dVec3.x;
	ssY >> d3dVec3.y;
	ssZ >> d3dVec3.z;

	return in;
}

std::stringstream & operator >> (std::stringstream & in, std::wstring & wStr)
{
	std::string curStr;

	in >> curStr;
	wStr = StrToWStr(curStr);

	return in;
}
