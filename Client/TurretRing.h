#ifndef TURRETRING_H
#define TURRETRING_H

#include "UserInterface.h"

class CTurret;
class CRingBox;

class CTurretRing final : public CUserInterface
{
public:
	explicit						CTurretRing				(CTurret* pTurret);
	virtual						   ~CTurretRing				(void);

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

private:


	GETTOR_SETTOR	(D3DXVECTOR3,	m_defaultSize,			DefaultSize);
	GETTOR_SETTOR	(CRingBox*,		m_pFocusedRingBox,		FocusedRingBox);
	GETTOR_SETTOR	(bool,			m_lastFrameActivated,	LastFrameActivated);

	GETTOR			(CTurret*,		m_pOwner,				Owner);
	GETTOR(std::vector<CRingBox*>,	m_vRingBoxes,			RingBoxes);

};

#endif