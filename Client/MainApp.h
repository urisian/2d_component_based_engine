#pragma once

class CMainApp final
{
public:
	CMainApp();
	~CMainApp();
public:
	HRESULT Ready_MainApp(); 
	void Update_MainApp(); 
	void Late_Update_MainApp(); 
	void Render_MainApp(); 
	void Release_MainApp(); 


};

