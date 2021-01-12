#ifndef COLLISIONHELPER_H
#define COLLISIONHELPER_H

class CObject;

namespace CollisionHelper
{
	bool PointRectCollision(D3DXVECTOR3 point, CObject* pObj);
};


#endif // !COLLISIONHELPER_H
