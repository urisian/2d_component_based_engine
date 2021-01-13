#ifndef TURRET_H
#define TURRET_H

#include "Object.h"

class CTurretRing;

class CTurret abstract : public CObject
{
public:
	explicit							CTurret				(void);
	virtual							   ~CTurret				(void);

	virtual			void				Initialize			(void);
	virtual			void				Update				(void);
	virtual			void				LateUpdate			(void);
	virtual			void				Release				(void);

protected:	
					void				Selected			(void);
					void				InitializeStates	(void);

	
	GETTOR			(int,				m_level,			Level);

	GETTOR			(int,				m_numOfSkill,		NumOfSkill);
	GETTOR			(int,				m_numOfRingBox,		NumOfRingBox);

	GETTOR			(int,				m_sellPrice,		SellPrice);

	GETTOR			(bool,				m_sellable,			Sellable);
	GETTOR			(bool,				m_rallyable,		Rallyable);	


	GETTOR			(CTurretRing*,		m_pTurretRing,		TurretRing);	
	GETTOR (std::vector<RingBoxInfo*>,	m_vRingBoxInfo,		RingBoxInfo); 
};

#endif