#ifndef RINGBOX_H
#define RINGBOX_H

#include "UserInterface.h"


class CTurretRing;

class CRingBox : public CUserInterface
{
public:
	explicit							CRingBox				(std::string objectKey);
	virtual							   ~CRingBox				(void);

					void				Initialize				(void);
					void				Update					(void);
					void				LateUpdate				(void);
					void				Release					(void);

private:
					void				PreInitialize			(void);

	GETTOR_SETTOR	(CTurretRing*,		m_pTurretRing,			TurretRing);
	GETTOR_SETTOR	(int,				m_price,				Price);
	GETTOR_SETTOR	(float,				m_anglePosition,		AnglePosition);
};

#endif