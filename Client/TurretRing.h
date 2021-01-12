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

	virtual			void			Initialize				(void);
	virtual			void			Update					(void);
	virtual			void			LateUpdate				(void);
	virtual			void			Release					(void);

	GETTOR(std::vector<CRingBox*>,	m_vRingBoxes,			RingBoxes);

private:
					CTurret*		m_pOwner;
					D3DXVECTOR3		m_defaultSize;
};

#endif