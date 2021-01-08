#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
class CTexture;

class CGraphicsComponent : public CComponent
{
public:
	explicit							CGraphicsComponent		(void);
									   ~CGraphicsComponent		(void);

					void				Initialize				(void);
					void				Update					(void); 

					int&				GetCurAniIndex			(void);
					int&				GetMaxAniIndex			(void);

					D3DXVECTOR3&		GetPosition				(void);
					D3DXVECTOR3&		GetRotation				(void);
					D3DXVECTOR3&		GetSize					(void);

					D3DCOLOR&			GetColor				(void);

					CTexture*			GetCTexture				(void);
					LPDIRECT3DTEXTURE9	GetTexture				(void);
private:
					int					m_curAniIndex;
					int					m_maxAniIndex;
				
					D3DXVECTOR3			m_position;
					D3DXVECTOR3			m_rotation;
					D3DXVECTOR3			m_size;

					D3DCOLOR			m_color;

					CTexture*			m_pCTexture;
					LPDIRECT3DTEXTURE9	m_pTexture;
};

#endif