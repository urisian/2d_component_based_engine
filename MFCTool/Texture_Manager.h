#pragma once
class CTexture; 
class CTexture_Manager
{
public:
	static CTexture_Manager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTexture_Manager; 
		return m_pInstance; 
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
public:
	enum TEX_ID { MULTI_TEX, SINGLE_TEX};
public:
	CTexture_Manager();
	~CTexture_Manager();
public:
	const TEXINFO* Get_TexInfo(const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const int& iIndex = 0);
	HRESULT Insert_Texture_Manager(TEX_ID eTexID, const wstring& wstrFilePath,const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const int& iIndex = 0);
	void Release_Texture_Manager(); 
private:
	static CTexture_Manager* m_pInstance; 
	// 여기에서 키값은 ObjectKey
	map<wstring, CTexture*> m_mapTexture; 
};

