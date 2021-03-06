#ifndef OBJECT_H
#define OBJECT_H

class CComponent;

class CObject abstract
{
public:
	explicit								CObject						(void);
	virtual								   ~CObject						(void);

	virtual			void					Initialize					(void);
	virtual			void					Update						(void);
	virtual			void					LateUpdate					(void);
	virtual			void					Release						(void);

	virtual			void					AddChildAndComponents		(void) PURE;
	virtual			void					InitializeComponents		(void) PURE;

					void					EraseElementFromMap			(std::string objectKey);
	virtual			void					StateChangeInit				(void);

					D3DXVECTOR3				GetFinalPos					(void);

protected:
	virtual			void					ReadDataFromStore			(void);

	GETTOR_SETTOR	(OBJID::ID,				m_objID,					ObjID);
	GETTOR_SETTOR	(DATAID::ID,			m_dataID,					DataID);

	GETTOR_SETTOR	(std::string,			m_objectKey,				ObjectKey);
	GETTOR_SETTOR	(std::string,			m_stateKey,					StateKey);
	GETTOR_SETTOR	(std::string,			m_basicStateKey,			BasicStateKey);

	GETTOR_SETTOR	(bool,					m_activated,				Activated);
	GETTOR_SETTOR	(bool,					m_needToBeDeleted,			NeedToBeDeleted);

	//Physics Component가 있다면 매 프레임 업데이트 해줌. 사이즈는 빼고.
	//Graphics Component가 있다면 매 프레임 받아가서 사용.
	GETTOR_SETTOR	(D3DXVECTOR3,			m_parentPosition,			ParentPosition);
	GETTOR_SETTOR	(D3DXVECTOR3,			m_position,					Position);
	GETTOR_SETTOR	(D3DXVECTOR3,			m_direction,				Direction);
	GETTOR_SETTOR	(D3DXVECTOR3,			m_rotation,					Rotation);
	GETTOR_SETTOR	(D3DXVECTOR3,			m_size,						Size);

	GETTOR			(CObject*,				m_pParent,					Parent);

protected:
	//오브젝트가 갖고 있는 컴포넌트들.
	std::map<std::string, CComponent*>		m_mComponents;
	std::vector<CObject*>					m_vChildren;


public:
	template <typename ComponentType>
	ComponentType* GetComponent(void)
	{
		std::string componentName = typeid(ComponentType).name();
		componentName.erase(0, 7);

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
		componentName.erase(0, 7);

		if ((pNewComponent = GetComponent<ComponentType>()) == nullptr)
		{
			pNewComponent = new ComponentType(this);
			m_mComponents[componentName] = pNewComponent;

			pNewComponent->Initialize();
		}

		return pNewComponent;
	}
};

#endif