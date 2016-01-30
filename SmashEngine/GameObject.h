#pragma once
#include "Component.h"
#include "ComponentType.h"
namespace SmashEngine
{
	class GameObject
	{
	public:
		GameObject(const std::string& name,unsigned int id);
		~GameObject(void);

		void				Initialize();
		void				Destroy();
		Component*			GetComponent(ComponentType typeID);
		void				AddComponent(ComponentType typeID, Component *component);
		unsigned int		GetId()const;
		const std::string&	GetName()const;
		template<typename type>
		type* GetComponentType(ComponentType typeId);
	private:
		std::string			ObjectName;
		bool				deleteThis;
		std::unordered_map<ComponentType, Component*> components;
		unsigned int		objectId;

	};

	template<typename type>
	type * GameObject::GetComponentType(ComponentType typeId)
	{
		return static_cast<type*>(GetComponent(typeId));
	}

#define has(type) GetComponentType<type>( TYPE_##type )
}