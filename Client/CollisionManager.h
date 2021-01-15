#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

class CClickableComponent;
class CCollisionComponent;

class CCollisionManager
{
public:
	static			CCollisionManager*		GetInstance					(void);
	static			void					DestroyInstance				(void);

					void					Initialize					(void);
					void					Update						(void);
					void					LateUpdate					(void);
					void					Release						(void);


					void					AddCollisionComponent		(CCollisionComponent* pCC);
					void					AddClickableComponent		(CClickableComponent* pCC);

	std::vector<CCollisionComponent*>		GetCollisionVector			(OBJID::ID	objID);

private:
	explicit								CCollisionManager			(void);
	virtual								   ~CCollisionManager			(void);

private:
	std::vector<CCollisionComponent*>		m_vCollisionComponent[OBJID::END];
	std::vector<CClickableComponent*>		m_vClickableComponent;
	static			CCollisionManager*		m_s_pInstance;
};

#endif