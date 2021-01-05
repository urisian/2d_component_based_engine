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
	// ������ �׸��� �����Ҷ� ����� Objectkey �ȿ� StateKey�� ���� �Ұ�. �� �̰� ��Ƽ �ؽ��� �� ��쿡��. 
	//�̱��ؽ��Ĵ� ������ƮŰ�� �ʿ��ϴ��� ������ƮŰ�� �ʿ䰡 ����. ��? ������ �׸��� ����ڶ�����. 
	virtual void Release_Texture() = 0; // PURE�� ����
};

