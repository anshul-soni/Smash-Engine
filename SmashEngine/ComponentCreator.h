#pragma once
#include "Component.h"
#include "ObjectFactory.h"
namespace SmashEngine
{
	class Component;

	class ComponentCreator
	{
	public:
		ComponentCreator(ComponentType typeId)
			:TypeId(typeId)
		{
		}

		ComponentType TypeId;
		virtual Component * Create() = 0;
	};

	template<typename type>
	class ComponentCreatorType : public ComponentCreator
	{
	public:
		ComponentCreatorType(ComponentType typeId)
			:ComponentCreator(typeId)
		{
		}

		virtual Component * Create()override
		{
			return new type();
		}
	};

};

#define RegisterComponent(type) GameObjectFactory::GetInstance().AddComponentCreator( #type, new ComponentCreatorType<type>( TYPE_##type ) );