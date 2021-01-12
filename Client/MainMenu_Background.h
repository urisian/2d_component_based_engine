#ifndef MAINMENU_BACKGROUND_H
#define MAINMENU_BACKGROUND_H

#include "Background.h"
class CMainMenu_Background : public CBackground
{
public:
	explicit					CMainMenu_Background		(void);
	virtual					   ~CMainMenu_Background		(void);

	virtual			void		Initialize					(void);
	virtual			void		Update						(void);
	virtual			void		LateUpdate					(void);
	virtual			void		Release						(void);
};

#endif