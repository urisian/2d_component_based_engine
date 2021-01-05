#pragma once
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();
public:
	virtual HRESULT Ready_GameObject() = 0; 
};

