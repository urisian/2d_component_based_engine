#pragma once
class CTexture abstract
{
public:
	explicit CTexture();
	virtual ~CTexture();
public:
	virtual const TEXINFO* Get_TexInfo(const wstring& wstrStateKey = L"",
		const int& iIndex = 0)PURE;
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath,
		const wstring& wstrStateKey = L"",
		const int& iIndex = 0)PURE;
	// 앞으로 그림을 보관할때 방법은 Objectkey 안에 StateKey가 존재 할것. 단 이건 멀티 텍스쳐 일 경우에만. 
	//싱글텍스쳐는 오브젝트키는 필요하더라도 스테이트키는 필요가 없다. 왜? 어차피 그림이 한장읶때문에. 
	virtual void Release_Texture() = 0; // PURE와 동일
};

