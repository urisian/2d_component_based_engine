#pragma once
class CGraphic_Device final
{
public:
	static CGraphic_Device* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CGraphic_Device; 

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
private:
	explicit CGraphic_Device();
	~CGraphic_Device();
	// 복사 생성자, 디폴트 대입연산자. 
	explicit CGraphic_Device(const CGraphic_Device& rObject) {};
	void operator=(const CGraphic_Device& rObject) {}; 

public:
	LPDIRECT3DDEVICE9 Get_Device() { return m_pDevice;  }
	LPD3DXSPRITE		Get_SPrite() { return m_pSprite; }

public:
	// 객체를 제어하기 위한 컴객체들을 생성 및 초기화 할 공간. 
	HRESULT Ready_Graphic_Device(); 
	void Release_Graphic_Device(); 
	void Render_Begin(); 
	void Render_End(); 

private:
	// 사용자가 사용하고자 하는 장치를 조사하고 해당 장치를 제어하기 위한 객채의 할당을 담당하는 com 객체 
	LPDIRECT3D9			m_pSDK; 
	LPDIRECT3DDEVICE9	m_pDevice; // 실질적으로 장치를 제어하는 com 객체. 
	LPD3DXSPRITE		m_pSprite; 
	//1. 장치를 제어하기 위한 컴객체를 생성을 먼저 하고. 
	//2. 이 제어하기 위한 SDK를 이용하여 그래픽카드의 지원 수준을 조사하고. 
	//3. 그래픽 카드의 지원 수준에 맞춰 장치를 제어하기 위한 컴객체를 생성한다. 
	/*
	com - component Object Model 의 약자로 우리가 배우는 다이렉트X에서 제공하는 부품단위의 객체들을 뜻한다. 
	개발환경에 상관없이 호환이 가능한 컴퍼넌트들의 사용을 위해 마이크로 소프트 사가 규정한 표준화된 방법이 바로 com 객체! 
	그냥 더 쉽게 레고를 생각해봐. 부품 한개 한개를 조립해서 결과물 나오듯 우리도 com 객체를 부품단위로 맞춰서 게임을 만든다 라는거. 

	*/
	static CGraphic_Device* m_pInstance; 
};

