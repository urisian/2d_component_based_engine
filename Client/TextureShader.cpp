#include "stdafx.h"
#include "TextureShader.h"
#include "DataStore.h"
#include "GraphicsManager.h"

CTextureShader::CTextureShader()
{
}


CTextureShader::~CTextureShader()
{
}

void CTextureShader::Initialize(void)
{

}

void CTextureShader::Release(void)
{
	if (m_pPixelShader)
	{
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}

	if (m_pVertexShader)
	{
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}
}

void CTextureShader::InitShader(void)
{
	HRESULT result;

	std::string vsPath, psPath;

	GET_VALUE(DATAID::ENGINE, GetCurClassName(this), "vsPath", vsPath);
	GET_VALUE(DATAID::ENGINE, GetCurClassName(this), "psPath", psPath);
	/* VertexShader 만들기 */
	/* 파일에서 버퍼로 컴파일함 */
	result = D3DXCompileShaderFromFile(StrToWStr(vsPath).c_str(), 0, 0, "VShader", "vs_2_0", 
										D3DXSHADER_DEBUG,
										&m_pShaderBuffer, &m_pErrorBuffer, &m_pConstantTable);
	if (FAILED(result))
		MessageBox(nullptr, L"Failed to compile VertexShader in InitShader", L"CTextureShader.cpp", MB_OK);

	//버퍼에서 쉐이더 포인터로 만들어줌.
	result = CGraphicsManager::GetInstance()->GetDevice()->
				CreateVertexShader((DWORD*)m_pShaderBuffer->GetBufferPointer(), &m_pVertexShader);
	if (FAILED(result))
		MessageBox(nullptr, L"Failed to create VertexShader in InitShader", L"CTextureShader.cpp", MB_OK);
	//다 쓴 버퍼는 릴리즈
	m_pShaderBuffer->Release();

	/* PixelShader 만들기 */
	/* 파일에서 버퍼로 컴파일함 */
	result = D3DXCompileShaderFromFile(StrToWStr(vsPath).c_str(), 0, 0, "PShader", "ps_2_0", 
										D3DXSHADER_DEBUG,
										&m_pShaderBuffer, &m_pErrorBuffer, &m_pConstantTable);
	if (FAILED(result))
		MessageBox(nullptr, L"Failed to compile PixelShader in InitShader", L"CTextureShader.cpp", MB_OK);

	//버퍼에서 쉐이더 포인터로 만들어줌.
	result = CGraphicsManager::GetInstance()->GetDevice()->
				CreatePixelShader((DWORD*)m_pShaderBuffer->GetBufferPointer(), &m_pPixelShader);
	if (FAILED(result))
		MessageBox(nullptr, L"Failed to create PixelShader in InitShader", L"CTextureShader.cpp", MB_OK);

	//다 쓴 버퍼는 릴리즈
	m_pShaderBuffer->Release();
}
