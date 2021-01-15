#ifndef TURRET_H
#define TURRET_H

#include "Object.h"

class CTurretRing;
class CDecoration;

class CTurret abstract : public CObject
{
public:
	explicit							CTurret				(void);
	virtual							   ~CTurret				(void);

	virtual			void				Initialize			(void);
	virtual			void				Update				(void);
	virtual			void				LateUpdate			(void);
	virtual			void				Release				(void);

	virtual			void				UpgradeTurret		(int increase = 1);
	virtual			void				SellTurret			(void);

protected:	
	virtual			void				ReadDataFromStore	(void);

					void				MakeRingBoxInfo		(void);
					void				MakeTurretRing		(void);
					void				MakeRangeCircle		(void);

					void				Selected			(void);
					void				FindTarget			(void);



	GETTOR_SETTOR	(CObject*,			m_pTarget,			Target);
	GETTOR_SETTOR	(int,				m_level,			Level);

	GETTOR			(int,				m_numOfSkill,		NumOfSkill);
	GETTOR			(int,				m_numOfRingBox,		NumOfRingBox);

	GETTOR			(bool,				m_sellable,			Sellable);
	GETTOR			(int,				m_sellPrice,		SellPrice);

	GETTOR			(bool,				m_rallyable,		Rallyable);	
	GETTOR			(bool,				m_rallyRange,		RallyRange);

	GETTOR			(float,				m_attackRange,		AttackRange);
	GETTOR			(float,				m_attackSpeed,		AttackSpeed);
	
	GETTOR			(float,				m_dmg,				Dmg);
	GETTOR			(float,				m_magicDmg,			MagicDmg);
	

	

	GETTOR			(CDecoration*,		m_pRangeCircle,		RangeCircle);
	GETTOR			(CTurretRing*,		m_pTurretRing,		TurretRing);	
	GETTOR (std::vector<RingBoxInfo*>,	m_vRingBoxInfo,		RingBoxInfo); 
};

#endif

