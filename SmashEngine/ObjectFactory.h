////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ObjectFactory.h															 
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
#include "ComponentCreator.h"
#include "System.h"
#include "GameObject.h"
#include "Component.h"
namespace SmashEngine
{
	class ComponentCreator;
	class ObjectFactory :
		public System
	{
	public:
		static ObjectFactory& GetInstance();
		void Init()override;
		void Update(float dt)override;
		SystemType GetType()const override;
		std::shared_ptr<GameObject> Create(const std::string& filename);
		void AddComponentCreator(const std::string& name, std::shared_ptr<ComponentCreator> creator);
		void Release()override;
		~ObjectFactory(void);
	private:
		const SystemType type;
		unsigned int lastObjectId;
		std::unordered_map<std::string, std::shared_ptr<ComponentCreator>> ComponentMap;
		ObjectFactory(void);
	};
}
