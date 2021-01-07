#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
class CTexture;

class CGraphicsComponent : public CComponent
{
public:
	explicit							CGraphicsComponent		(void);
									   ~CGraphicsComponent		(void);

					D3DXVECTOR3&		GetPosition				(void);
					D3DXVECTOR3&		GetRotation				(void);
					D3DXVECTOR3&		GetScale				(void);

					CTexture*			GetCTexture				(void);
private:
					D3DXVECTOR3			m_position;
					D3DXVECTOR3			m_rotation;
					D3DXVECTOR3			m_scale;
					CTexture*			m_pCTexture;
};

#endif