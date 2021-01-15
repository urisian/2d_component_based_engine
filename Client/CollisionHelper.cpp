#include "stdafx.h"
#include "CollisionHelper.h"
#include "Object.h"

bool CollisionHelper::PointRectCollision(D3DXVECTOR3 point, CObject * pObj)
{
	D3DXVECTOR3 objMinPoint, objMaxPoint;

	objMinPoint = pObj->GetParentPosition() + pObj->GetPosition() - (pObj->GetSize() / 2.f);
	objMaxPoint = pObj->GetParentPosition() + pObj->GetPosition() + (pObj->GetSize() / 2.f);
	if (point.x < objMinPoint.x || point.x > objMaxPoint.x ||
		point.y < objMinPoint.y || point.y > objMaxPoint.y)
		return false;

	return true;
}

bool CollisionHelper::PointEclipseCollision(D3DXVECTOR3 point, D3DXVECTOR3 eclipsePos, D3DXVECTOR3 eclipseSize)
{
	if ((pow((point.x - eclipsePos.x), 2) / pow(eclipseSize.x/2.f, 2)) + (pow((point.y - eclipsePos.y), 2) / pow(eclipseSize.y/2.f, 2)) > 1)
		return false;

	return true;
}