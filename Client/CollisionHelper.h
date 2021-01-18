#ifndef COLLISIONHELPER_H
#define COLLISIONHELPER_H

class CObject;
class CCollisionComponent;
namespace CollisionHelper
{
	bool PointRectCollision		(D3DXVECTOR3 point, CObject* pObj);
	bool PointCircleCollision	(CCollisionComponent* pCC1, CCollisionComponent* pCC2);

	bool PointEclipseCollision	(D3DXVECTOR3 point, D3DXVECTOR3 eclipsePos, D3DXVECTOR3 eclipseSize);
};


#endif // !COLLISIONHELPER_H
