#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"

class CObject;
class CPhysicsComponent : public CComponent
{
public:
	explicit							CPhysicsComponent		(CObject* pOwner);
									   ~CPhysicsComponent		(void);

					void				Initialize				(void);
					void				Update					(void); 
					void				LateUpdate				(void);
					void				Release					(void);

					void				StateChangeInit			(void);

	GETTOR_SETTOR	(D3DXVECTOR3,		m_position,				Position);
	GETTOR_SETTOR	(D3DXVECTOR3,		m_direction,			Direction);

	GETTOR_SETTOR	(float,				m_speed,				Speed);
};

#endif

