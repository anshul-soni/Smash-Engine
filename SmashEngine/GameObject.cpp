#include "stdafx.h"
#include "GameObject.h"

namespace SmashEngine
{
	GameObject::GameObject(const std::string& name, unsigned int id) :ObjectName(name), deleteThis(false), objectId(id)
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
		for (auto component:components)
		{
			component.second->object = this;
			component.second->Initialize();
		}
	}

	void GameObject::Destroy()
	{
	}

	Component* GameObject::GetComponent(ComponentType typeID)
	{
		if (components.find(typeID)!=components.end())
		{
			return components[typeID];
		}
		return nullptr;
	}

	void GameObject::AddComponent(ComponentType typeID, Component* component)
	{
		if (components.find(typeID) == components.end())
		{
			components[typeID] = component;
		}
	}

	unsigned GameObject::GetId() const
	{
		return objectId;
	}

	const std::string& GameObject::GetName() const
	{
		return ObjectName;
	}
}