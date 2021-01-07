#pragma once

class CMainApp final
{
public:
						CMainApp				(void);
					   ~CMainApp				(void);
public:
	void				Initialize				(void); 
	void				Update					(void); 
	void				LateUpdate				(void); 
	void				Release					(void);
};

