#ifndef COLLISIONHELPER_H
#define COLLISIONHELPER_H

class CObject;

namespace CollisionHelper
{
	bool PointRectCollision(D3DXVECTOR3 point, CObject* pObj);
	bool PointEclipseCollision(D3DXVECTOR3 point, D3DXVECTOR3 eclipsePos, D3DXVECTOR3 eclipseSize);
};


#endif // !COLLISIONHELPER_H
