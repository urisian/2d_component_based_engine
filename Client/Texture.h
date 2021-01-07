#ifndef TEXTURE_H
#define TEXTURE_H

class CTexture
{
public:
	explicit								CTexture			(void);
	virtual								   ~CTexture			(void);

				bool						InsertTexInfo		(const std::string& fullPath);
				std::vector<TEXINFO*>&		GetTexInfos			(const std::string& stateKey);
private:
				std::string					GetStateKey			(const std::string& fullPath);
private:
	//First�� StateKey, Second�� TexInfo ����.
	std::map<std::string, std::vector<TEXINFO*>> m_mTexInfo;
};

#endif