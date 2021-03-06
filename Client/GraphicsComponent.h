#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
class CTexture;
class CAnimation;

class CGraphicsComponent : public CComponent
{
public:
	explicit								CGraphicsComponent		(CObject* pOwner);
										   ~CGraphicsComponent		(void);

					void					Initialize				(void);
					void					Update					(void); 
					void					LateUpdate				(void);
					void					Release					(void);

					void					StateChangeInit			(void);


	GETTOR_SETTOR	(bool,					m_isOrtho,				IsOrtho);
	GETTOR_SETTOR	(int,					m_zOrder,				ZOrder);

	GETTOR_SETTOR	(D3DXVECTOR3,			m_position,				Position);
	GETTOR_SETTOR	(D3DXVECTOR3,			m_rotation,				Rotation);
	GETTOR_SETTOR	(D3DXVECTOR3,			m_size,					Size);

	GETTOR_SETTOR	(D3DXCOLOR,				m_color,				Color);

	GETTOR_SETTOR	(CTexture*,				m_pCTexture,			CTexture);
	GETTOR_SETTOR	(CAnimation*,			m_pAnimation,			Animation);

	GETTOR_SETTOR	(bool,					m_xFlip,				XFlip);

	GETTOR_SETTOR	(LPDIRECT3DTEXTURE9,	m_pTexture,				Texture);					
};

#endif