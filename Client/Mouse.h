#ifndef MOUSE_H
#define MOUSE_H

#include "UserInterface.h"
class CMouse final : public CUserInterface
{
public:
	explicit							CMouse					(void);
									   ~CMouse					(void);

					void				Initialize				(void);
					void				Update					(void);
					void				LateUpdate				(void);
					void				Release					(void);

					void				AddChildAndComponents	(void);
					void				InitializeComponents	(void);
};

#endif
