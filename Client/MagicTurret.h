#ifndef MAGICTURRET_H
#define MAGICTURRET_H

#include "Turret.h"

class CMagicianUnit;

class CMagicTurret final : public CTurret
{
public:
	explicit							CMagicTurret				(void);
									   ~CMagicTurret				(void);

					void				Initialize					(void);
					void				Update						(void);
					void				LateUpdate					(void);
					void				Release						(void);

					void				UpgradeTurret				(int increase = 1);

					void				AddChildAndComponents		(void);
					void				InitializeComponents		(void);

	GETTOR			(CMagicianUnit*,	m_pMagician,				Magician);


};

#endif