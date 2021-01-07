#include "stdafx.h"
#include "Camera.h"
#include "DataStore.h"
#include "Application.h"
#include "GraphicsManager.h"

CCamera::CCamera()
{
	m_position		= {};
	m_rotation		= {};
	m_target		= {};
	m_up			= {};
	m_right			= {};

	m_viewMatrix	= {};
	m_projMatrix	= {};

	m_zMaxPos		= 0.f;
	m_zMinPos		= 0.f;
	m_zDefaultPos	= 0.f;

	m_fov			= 0.f;
	m_aspect		= 0.f;
	m_nearPlane		= 0.f;
	m_farPlane		= 0.f;

	m_cameraHeight	= 0.f;
	m_cameraWidth	= 0.f;
}


CCamera::~CCamera()
{
}

void CCamera::Initialize(void)
{
	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_position", m_position);
	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_rotation", m_rotation);
	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_target", m_target);
	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_up", m_up);
	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_right", m_right);

	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_zMaxPos", m_zMaxPos);
	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_zMinPos", m_zMinPos);
	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_zDefaultPos", m_zDefaultPos);

	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_fov", m_fov);
	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_nearPlane", m_nearPlane);
	GET_VALUE(DATAID::ENGINE, GetComponentName(this), "m_farPlane", m_farPlane);

	m_aspect		= static_cast<float>(CApplication::GetInstance()->GetWndWidth()) 
					/ static_cast<float>(CApplication::GetInstance()->GetWndHeight());

	m_cameraHeight	= abs(m_position.z) * tan(D3DX_PI/8) * 2;
	m_cameraWidth	= m_cameraHeight * m_aspect;
}

void CCamera::Update(void)
{
	UpdateViewMatrix();
	UpdateProjMatrix();
}

void CCamera::UpdateViewMatrix(void)
{
	D3DXVECTOR3 up, lookAt;
	float pitch, yaw, roll;
	D3DXMATRIX rotationMatrix;

	up		= m_up;
	lookAt	= m_target;

	pitch	= D3DXToRadian(m_rotation.x);
	yaw		= D3DXToRadian(m_rotation.y);
	roll	= D3DXToRadian(m_rotation.z);

	//카메라의 rotation에 따라서 rotationMatrix를 구성한다.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	//viewMatrix를 구성할 up벡터와 lookAt벡터를 회전시킨 값을 구한다.
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);

	//looAt벡터의 포지션을 업데이트 해준다
	lookAt += m_position;

	//ViewMatrix를 계산한다.
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &lookAt, &up);
	CGraphicsManager::GetInstance()->GetDevice()->SetTransform(D3DTS_VIEW, &m_viewMatrix);
}

void CCamera::UpdateProjMatrix(void)
{
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, m_fov, m_aspect, m_nearPlane, m_farPlane);
	CGraphicsManager::GetInstance()->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_projMatrix);
}
