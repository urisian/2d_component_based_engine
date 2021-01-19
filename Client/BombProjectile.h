#ifndef BOMBPROJECTILE_H
#define BOMBPROJECTILE_H

#include "Projectile.h"
class CBombProjectile final :public CProjectile
{
public:
	explicit						CBombProjectile			(CObject* pShooter);
								   ~CBombProjectile			(void);

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

					void			AddChildAndComponents	(void);
					void			InitializeComponents	(void);

private:
					void			HitTarget				(void);
					void			AfterHit				(void);

	GETTOR			(D3DXVECTOR3,	m_explodeRange,			ExplodeRange);
	GETTOR			(D3DXVECTOR3,	m_ground,				Ground);
};

#endif