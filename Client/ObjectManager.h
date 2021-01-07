#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

class CObject;

class CObjectManager
{
public:
	static			CObjectManager*				GetInstance			(void);
	static			void						DestroyInstance		(void);

					void						Initialize			(void);
					void						Update				(void);
					void						LateUpdate			(void);
					void						Release				(void);

					void						Add_Object			(CObject* pObj, OBJID::ID objID);
					std::vector<CObject*>		(&GetObjectList		(void)) [OBJID::END];
private:
	explicit									CObjectManager		(void);
											   ~CObjectManager		(void);

private:

	static			CObjectManager*				m_s_pInstance;
					std::vector<CObject*>		m_vObjects[OBJID::END];
};

#endif