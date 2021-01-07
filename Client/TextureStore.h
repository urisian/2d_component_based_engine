#ifndef CTEXTURESTORE_H
#define CTEXTURESTORE_H

class CTexture;

class CTextureStore
{
public:
	static		CTextureStore*			GetInstance				(void);
	static		void					DestroyInstance			(void);

				void					Initialize				(void);
				void					Release					(void);


private:
	explicit							CTextureStore			(void);
	virtual							   ~CTextureStore			(void);

				bool					CreateTexture			(const std::string& fullPath);
				std::string				GetSectionKey			(const std::string& fullPath);
				std::string				GetObjectKey			(const std::string& fullPath);
				std::string				GetStateKey				(const std::string& fullPath);


				std::string				m_resourcePath;
	static		CTextureStore*			m_s_pInstance;
	std::map<std::string, CTexture*>	m_mTexture[TEXID::END];
};

#endif