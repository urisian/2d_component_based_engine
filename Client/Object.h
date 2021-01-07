#ifndef OBJECT_H
#define OBJECT_H

class CComponent;

class CObject abstract
{
public:
	explicit								CObject				(void);
	virtual								   ~CObject				(void);

	virtual			void					Update				(void) PURE;
	virtual			void					LateUpdate			(void) PURE;
	virtual			void					Release				(void) PURE;

					OBJID::ID				GetObjID			(void);
					DATAID::ID				GetDataID			(void);
					std::string&			GetObjectKey		(void);

					std::string&			GetStateKey			(void);
					void					SetStateKey			(std::string stateKey);


					bool					GetActivated		(void) const;
					void					SetActivated		(bool activated);

					bool					GetNeedToBeDeleted	(void) const;
					void					SetNeedToBeDeleted	(bool needToBeDeleted);

public:


protected:

					OBJID::ID				m_objID;
					DATAID::ID				m_dataID;

					std::string				m_objectKey;
					std::string				m_stateKey;

					bool					m_activated;
					bool					m_needToBeDeleted;
	//오브젝트가 갖고 있는 컴포넌트들.
	std::map<std::string, CComponent*>		m_mComponents;

public:
	template <typename ComponentType>
	ComponentType* GetComponent(void)
	{
		std::string componentName = typeid(ComponentType).name();
		componentName.erase(0, 6);

		auto& it = m_mComponents.find(componentName);
		if (it == m_mComponents.end())
			return nullptr;

		return static_cast<ComponentType*>(it->second);
	}

	template <typename ComponentType>
	ComponentType* AddComponent(void)
	{
		ComponentType* pNewComponent = nullptr;
		std::string componentName = typeid(ComponentType).name();
		componentName.erase(0, 6);

		if ((pNewComponent = GetComponent<ComponentType>()) == nullptr)
		{
			pNewComponent = new ComponentType;
			pNewComponent->SetOwner(this);
			m_mComponents[componentName] = pNewComponent;
		}

		return pNewComponent;
	}
};

#endif