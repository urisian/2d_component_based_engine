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
	// ���� ������, ����Ʈ ���Կ�����. 
	explicit CGraphic_Device(const CGraphic_Device& rObject) {};
	void operator=(const CGraphic_Device& rObject) {}; 

public:
	LPDIRECT3DDEVICE9 Get_Device() { return m_pDevice;  }
	LPD3DXSPRITE		Get_SPrite() { return m_pSprite; }

public:
	// ��ü�� �����ϱ� ���� �İ�ü���� ���� �� �ʱ�ȭ �� ����. 
	HRESULT Ready_Graphic_Device(); 
	void Release_Graphic_Device(); 
	void Render_Begin(); 
	void Render_End(); 

private:
	// ����ڰ� ����ϰ��� �ϴ� ��ġ�� �����ϰ� �ش� ��ġ�� �����ϱ� ���� ��ä�� �Ҵ��� ����ϴ� com ��ü 
	LPDIRECT3D9			m_pSDK; 
	LPDIRECT3DDEVICE9	m_pDevice; // ���������� ��ġ�� �����ϴ� com ��ü. 
	LPD3DXSPRITE		m_pSprite; 
	//1. ��ġ�� �����ϱ� ���� �İ�ü�� ������ ���� �ϰ�. 
	//2. �� �����ϱ� ���� SDK�� �̿��Ͽ� �׷���ī���� ���� ������ �����ϰ�. 
	//3. �׷��� ī���� ���� ���ؿ� ���� ��ġ�� �����ϱ� ���� �İ�ü�� �����Ѵ�. 
	/*
	com - component Object Model �� ���ڷ� �츮�� ���� ���̷�ƮX���� �����ϴ� ��ǰ������ ��ü���� ���Ѵ�. 
	����ȯ�濡 ������� ȣȯ�� ������ ���۳�Ʈ���� ����� ���� ����ũ�� ����Ʈ �簡 ������ ǥ��ȭ�� ����� �ٷ� com ��ü! 
	�׳� �� ���� ���� �����غ�. ��ǰ �Ѱ� �Ѱ��� �����ؼ� ����� ������ �츮�� com ��ü�� ��ǰ������ ���缭 ������ ����� ��°�. 

	*/
	static CGraphic_Device* m_pInstance; 
};

