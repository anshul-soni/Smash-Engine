////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ComponentCreator.h															 
/// @date 1/26/2016  7:43 PM			 
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
#include "ObjectFactory.h"
#include <memory>
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
		virtual std::shared_ptr<Component> Create() = 0;
	};

	template<typename type>
	class ComponentCreatorType : public ComponentCreator
	{
	public:
		ComponentCreatorType(ComponentType typeId)
			:ComponentCreator(typeId)
		{
		}

		virtual std::shared_ptr<Component> Create()override
		{
            return std::make_shared<type>();
		}
	};

};

#define RegisterComponent(type) ObjectFactory::GetInstance().AddComponentCreator( #type, std::make_shared<ComponentCreatorType<type>>( TYPE_##type ) );