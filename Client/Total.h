#pragma once
typedef struct tagInfo
{
	//D3DXVECTOR2; 
	//D3DXVECTOR3; 
	//D3DXVECTOR4;
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize; 
	D3DXVECTOR3 vDir; 
	D3DXVECTOR3 vLook; // - 단순 기준
	D3DXMATRIX matWorld;
}INFO;