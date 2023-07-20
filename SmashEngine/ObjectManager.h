////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ObjectManager.h															 
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
#include "System.h"
#include "GameObject.h"

namespace SmashEngine
{
	class ObjectManager
	{
	public:
		static void Start();
		static void Stop();
		static ObjectManager& GetInstance();
		void Update(float dt);
		void AddObject(std::shared_ptr<GameObject> object);
		void DeleteObject(std::shared_ptr<GameObject> object);
		void DeleteObject(const std::string objectName);
		void DeleteObject(const unsigned int objectId);
		const std::unordered_map<unsigned, std::shared_ptr<GameObject>>& GetObjects()const;
		~ObjectManager(void);
	private:
		ObjectManager(void);
		std::unordered_map<unsigned, std::shared_ptr<GameObject>> gameObjects;
		std::set<std::shared_ptr<GameObject>> objectsToBeDeleted;
		ObjectManager(const ObjectManager&) = delete;
		ObjectManager& operator=(const ObjectManager) = delete;
		static ObjectManager* instance;
	};
}