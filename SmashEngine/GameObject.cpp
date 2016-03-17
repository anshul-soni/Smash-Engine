////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file GameObject.cpp															 
/// @date 1/29/2016  5:32 PM			 
/// @author Anshul Soni <soni.anshul93@gmail.com>								 
///																				 
/// As a condition of your accessing this Engine, you agree to be bound 		 
///	by the following terms and conditions: 										 
/// The software was created by Anshul Soni, and all copyright and other 		 
///	rights in such is owned by Anshul Soni. While you are allowed to access,  	 
/// download and use the code for non-commercial, home use you hereby expressly  
/// agree that you will not otherwise copy, distribute, modify, the code. 		 
////////////////////////////////////////////////////////////////////////////////////
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