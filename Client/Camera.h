#pragma once
class CCamera
{
public:
						CCamera				(void);
					   ~CCamera				(void);

	void				Initialize			(void);
	void				Update				(void);

	
private:
	void				UpdateViewMatrix	(void);
	void				UpdateProjMatrix	(void);

public:
	D3DXVECTOR3			m_position;
	D3DXVECTOR3			m_rotation;
	D3DXVECTOR3			m_target;
	D3DXVECTOR3			m_up;
	D3DXVECTOR3			m_right;

	D3DXMATRIX			m_viewMatrix;
	D3DXMATRIX			m_projMatrix;

	float				m_zMaxPos;
	float				m_zMinPos;
	float				m_zDefaultPos;

	float				m_fov;
	float				m_aspect;
	float				m_nearPlane;
	float				m_farPlane;

	float				m_cameraHeight;
	float				m_cameraWidth;


};

