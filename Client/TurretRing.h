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

					void			AddChildAndComponents	(void);
					void			InitializeComponents	(void);
private:
					void			MakeRingBoxes			(void);

	GETTOR_SETTOR	(D3DXVECTOR3,	m_defaultSize,			DefaultSize);
	GETTOR_SETTOR	(CRingBox*,		m_pFocusedRingBox,		FocusedRingBox);
	GETTOR_SETTOR	(bool,			m_lastFrameActivated,	LastFrameActivated);

	GETTOR(std::vector<CRingBox*>,	m_vRingBoxes,			RingBoxes);

};

#endif