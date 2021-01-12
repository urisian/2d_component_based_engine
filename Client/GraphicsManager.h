#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

class CGraphicsComponent;
class CCamera;
class CObject;

class CGraphicsManager
{
public:
	static			CGraphicsManager*			GetInstance				(void);
	static			void						DestroyInstance			(void);

					void						Initialize				(void);
					void						Update					(void);
					void						LateUpdate				(void);
					void						Release					(void);
	
					void						AddGraphicsComponent	(CGraphicsComponent* pGC);
	
	GETTOR			(LPDIRECT3DDEVICE9,			m_pDevice,				Device);

private:
												CGraphicsManager		(void);
											   ~CGraphicsManager		(void);

					void						InitDevice				(void);
					void						InitVertexBuffer		(void);
					void						InitIndexBuffer			(void);
					void						InitStates				(void);

					void						SetWorldMatrix			(CGraphicsComponent* pGC);
private:
	
					int							m_screenWidth;
					int							m_screenHeight;

					D3DPRESENT_PARAMETERS       m_d3dpParm;

					LPDIRECT3D9                 m_pD3D;
					
					LPDIRECT3DVERTEXBUFFER9     m_pVertexBuffer;
					LPDIRECT3DINDEXBUFFER9      m_pIndexBuffer;

					CCamera*					m_pCamera;

	std::vector<CGraphicsComponent*>			m_vGraphicsComponents;

	static			CGraphicsManager*			m_s_pInstance;
};

#endif