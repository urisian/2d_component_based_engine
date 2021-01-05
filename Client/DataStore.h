#ifndef CDATASTORE_H
#define CDATASTORE_H

#include <fstream>
#include <sstream>

class CDataStore
{
public:
	static		CDataStore*		GetInstance			(void);
	static		void			DestroyInstance		(void);

				void			Initialize			(void);
				void			Release				(void);

private:
	explicit					CDataStore			(void);
	virtual					   ~CDataStore			(void);

				void			ReadFile			(const std::string& fullPath);
				std::string		GetSectionKey		(const std::string& fullPath);
				std::string		GetObjectKey		(const std::string& fullPath);
				std::string		GetVariableKey		(const std::string& lineFromFile);
				std::string		GetKeyValue			(const std::string& lineFromFile);

	friend		std::stringstream& operator	>>	(std::stringstream& in, D3DXVECTOR3& d3dVec3);
	friend		std::stringstream& operator	>>	(std::stringstream& in, std::wstring& wStr);

private:
				std::string		m_resourcePath;
	static		CDataStore*		m_s_pInstance;

	std::map<std::string, std::map<std::string, std::string>> m_mDataMap[DATAID::END];


public:
	template <typename T>
	void GetValue(DATAID::ID dataID, std::string objectKey, std::string varKey, T& result)
	{
#if _DEBUG
		if (m_mDataMap[dataID].find(objectKey) == m_mDataMap[dataID].end())
		{
			MessageBox(nullptr, StrToWStr(objectKey + " missing objectKey in GetValue function").c_str(), L"DataStore", MB_OK);
			return;
		}
		if (m_mDataMap[dataID].find(objectKey)->second.find(varKey) == m_mDataMap[dataID].find(objectKey)->second.end())
		{
			MessageBox(nullptr, StrToWStr(varKey + " missing varKey in GetValue function").c_str(), L"DataStore", MB_OK);
			return;
		}
#endif

		std::stringstream ss(m_mDataMap[dataID].find(objectKey)->second.find(varKey)->second);

		ss << std::boolalpha;
		ss >> result;
	}
};


#endif