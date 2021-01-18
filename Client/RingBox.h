#ifndef RINGBOX_H
#define RINGBOX_H

#include "UserInterface.h"


class CTurretRing;

class CRingBox final : public CUserInterface
{
public:
	explicit							CRingBox				(CTurretRing* pParent, std::string objectKey);
	virtual							   ~CRingBox				(void);

					void				Initialize				(void);
					void				Update					(void);
					void				LateUpdate				(void);
					void				Release					(void);

					void				AddChildAndComponents	(void);
					void				InitializeComponents	(void);

					void				Selected				(void);

	GETTOR_SETTOR	(int,				m_price,				Price);
	GETTOR_SETTOR	(float,				m_anglePosition,		AnglePosition);
};

#endif