#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"

class CDecoration;

class CCollisionComponent : public CComponent
{
public:
	explicit							CCollisionComponent			(CObject* pOwner);
									   ~CCollisionComponent			(void);

					void				Initialize					(void);
					void				Update						(void);
					void				LateUpdate					(void);
					void				Release						(void);

					void				StateChangeInit				(void);
	
	GETTOR_SETTOR	(bool,				m_showDebug,				ShowDebug);
	GETTOR_SETTOR	(CDecoration*,		m_pDebugDraw,				DebugDraw);

	GETTOR_SETTOR	(D3DXVECTOR3,		m_position,					Position);

	GETTOR_SETTOR	(D3DXVECTOR3,		m_halfExtent,				HalfExtent);
	GETTOR_SETTOR	(float,				m_radius,					Radius);
};

#endif