#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

class CPhysicsComponent;

class CPhysicsManager
{
public:
	static			CPhysicsManager*			GetInstance				(void);
	static			void						DestroyInstance			(void);

					void						Initialize				(void);
					void						Update					(void);
					void						LateUpdate				(void);
					void						Release					(void);

					void						AddPhysicsComponent		(CPhysicsComponent* pPC);
private:
	explicit									CPhysicsManager			(void);
	virtual									   ~CPhysicsManager			(void);


private:
	std::vector<CPhysicsComponent*>				m_vPhysicsComponents;
	static			CPhysicsManager*			m_s_pInstance;
};

#endif