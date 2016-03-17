////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ObjectManager.cpp															 
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
#include "ObjectManager.h"

namespace SmashEngine
{
	ObjectManager::ObjectManager() :type(SYSTEM_ObjectManager)
	{
	}

	ObjectManager& ObjectManager::GetInstance()
	{
		static ObjectManager instance;
			return instance;
	}

	void ObjectManager::Init()
	{
	}

	void ObjectManager::Update(float dt)
	{
		for (auto object : objectsToBeDeleted)
		{
			//make sure that the object exists and was not already deleted
			if(gameObjects.find(object->GetId())!=gameObjects.end())
			{
				auto id = object->GetId();
				delete object;
				gameObjects.erase(id);
			}
		}
		objectsToBeDeleted.clear();
	}

	void ObjectManager::Release()
	{
	}

	void ObjectManager::AddObject(GameObject* object)
	{
		gameObjects[object->GetId()] = object;
	}

	void ObjectManager::DeleteObject(GameObject* object)
	{
		if (gameObjects.find(object->GetId())!=gameObjects.end())
		{
			objectsToBeDeleted.insert(gameObjects[object->GetId()]);
		}
	}

	void ObjectManager::DeleteObject(const std::string objectName)
	{
		for (auto object:gameObjects)
		{
			if (object.second->GetName()==objectName)
			{
				objectsToBeDeleted.insert(object.second);
			}
		}
	}

	void ObjectManager::DeleteObject(const unsigned objectId)
	{
		if (gameObjects.find(objectId) != gameObjects.end())
		{
			objectsToBeDeleted.insert(gameObjects[objectId]);
		}
	}

	const std::unordered_map<unsigned, GameObject*>& ObjectManager::GetObjects() const
	{
		return gameObjects;
	}

	SystemType ObjectManager::GetType() const
	{
		return type;
	}

	ObjectManager::~ObjectManager()
	{
	}
}