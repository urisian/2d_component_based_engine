#ifndef CLICKABLECOMPONENT_H
#define CLICKABLECOMPONENT_H

#include "Component.h"

#include <functional>

class CObject;
class CClickableComponent : public CComponent
{
public:
	explicit						CClickableComponent			(CObject* pOwner);
	virtual						   ~CClickableComponent			(void);

					void			Initialize					(void);
					void			Update						(void); 
					void			LateUpdate					(void);
					void			Release						(void);

	GETTOR_SETTOR	(bool,			m_mouseOver,				MouseOver);
	GETTOR_SETTOR	(bool,			m_clickDown,				ClickDown);
	GETTOR_SETTOR	(bool,			m_clickUp,					ClickUp);
	GETTOR_SETTOR	(int,			m_cOrder,					COrder);

					void			SetPlayFunc					(std::function<void(void)> funcPointer);


private:
					void			CheckMouseOver				(void);
					void			CheckClickDown				(void);
					void			CheckClickUp				(void);

					std::function<void(void)> m_fpPlay;
};

#endif
