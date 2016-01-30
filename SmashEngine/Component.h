#pragma once
#include "ComponentType.h"
#include "stdafx.h"
#include "tinyxml2.h"

namespace SmashEngine
{
	class GameObject;
	class Component
	{
		friend class GameObject;
	public:
		Component() :typeId(TYPE_None), object(nullptr){};
		virtual void	Initialize(){}
		virtual void	Deserialize(tinyxml2::XMLElement* pElement){}
		virtual void	Destroy(){}
		GameObject*		GetOwner()const{ return object; }
	private:
		ComponentType	typeId;
		GameObject*		object;
	protected:
		virtual ~Component(){};
	};
}
