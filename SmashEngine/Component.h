////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Component.h															 
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
		virtual void	Update(float dt){}
		virtual void	Destroy(){}
		GameObject*		GetOwner()const{ return object; }
	private:
		ComponentType	typeId;
		GameObject*		object;
	protected:
		virtual ~Component(){};
	};
}
