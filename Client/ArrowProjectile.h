#ifndef ARROWPROJECTILE_H
#define ARROWPROJECTILE_H

#include "Projectile.h"

class CArrowProjectile final : public CProjectile
{
public:
	explicit						CArrowProjectile		(CObject* pShooter);
	virtual						   ~CArrowProjectile		(void);

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

					void			AddChildAndComponents	(void);
					void			InitializeComponents	(void);

private:
					void			HitTarget				(void);
					void			AfterHit				(void);

	GETTOR			(D3DXVECTOR3,	m_ground,				Ground);
};

#endif