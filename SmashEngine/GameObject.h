////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file GameObject.h															 
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
#include "Component.h"
#include "ComponentType.h"
#include <memory>

namespace SmashEngine
{
	class GameObject
	{
	public:
		GameObject(const std::string& name,unsigned int id);
		~GameObject(void);

		void				                                          Initialize();
		void				                                          Destroy();
		std::shared_ptr<Component>			                          GetComponent(ComponentType typeID);
		void				                                          AddComponent(ComponentType typeID,std::shared_ptr<Component> component);
		unsigned int		                                          GetId()const;
		const std::string&	                                          GetName()const;
		template<typename type>
        std::shared_ptr<type>                                         GetComponentType(ComponentType typeId);
	private:
		std::string			                                          ObjectName;
		bool				                                          deleteThis;
		std::unordered_map<ComponentType, std::shared_ptr<Component>> components;
		unsigned int		                                          objectId;

	};

	template<typename type>
	std::shared_ptr<type>  GameObject::GetComponentType(ComponentType typeId)
	{
		return std::static_pointer_cast<type>(GetComponent(typeId));
	}

#define has(type) GetComponentType<type>( TYPE_##type )
}