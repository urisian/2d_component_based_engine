#ifndef MAGICBALLPROJECTILE_H
#define MAGICBALLPROJECTILE_H

#include "Projectile.h"
class CMagicBallProjectile : public CProjectile
{
public:
	explicit						CMagicBallProjectile	(CObject* pShooter);
	virtual						   ~CMagicBallProjectile	(void);

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

					void			AddChildAndComponents	(void);
					void			InitializeComponents	(void);

private:
					void			HitTarget				(void);
					void			AfterHit				(void);
};
#endif