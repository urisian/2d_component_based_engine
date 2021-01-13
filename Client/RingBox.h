#ifndef RINGBOX_H
#define RINGBOX_H

#include "UserInterface.h"


class CTurretRing;

class CRingBox final : public CUserInterface
{
public:
	explicit							CRingBox				(std::string objectKey);
	virtual							   ~CRingBox				(void);

					void				Initialize				(void);
					void				Update					(void);
					void				LateUpdate				(void);
					void				Release					(void);

					void				Selected				(void);

	GETTOR_SETTOR	(RBTYPE::TYPE,		m_type,					Type);
	GETTOR_SETTOR	(CTurretRing*,		m_pTurretRing,			TurretRing);
	GETTOR_SETTOR	(int,				m_price,				Price);
	GETTOR_SETTOR	(float,				m_anglePosition,		AnglePosition);
};

#endif