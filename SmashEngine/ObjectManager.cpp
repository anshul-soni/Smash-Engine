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
	ObjectManager* ObjectManager::instance = nullptr;
	ObjectManager::ObjectManager()
	{
	}

	void ObjectManager::Start()
	{
		if(instance)
		{
			return;
		}
		instance = new ObjectManager();
	}

	void ObjectManager::Stop()
	{
		
	}

	ObjectManager& ObjectManager::GetInstance()
	{
		if (instance)
		{
			return *instance;
		}
		Start();
		return *instance;
	}

	void ObjectManager::Update(float dt)
	{
		for (auto object : objectsToBeDeleted)
		{
			//make sure that the object exists and was not already deleted
			if(gameObjects.find(object->GetId())!=gameObjects.end())
			{
				unsigned int id = object->GetId();
				gameObjects.erase(id);
			}
		}
		objectsToBeDeleted.clear();
	}

	void ObjectManager::AddObject(std::shared_ptr<GameObject> object)
	{
		gameObjects[object->GetId()] = object;
	}

	void ObjectManager::DeleteObject(std::shared_ptr<GameObject> object)
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

	void ObjectManager::DeleteObject(const unsigned int objectId)
	{
		if (gameObjects.find(objectId) != gameObjects.end())
		{
			objectsToBeDeleted.insert(gameObjects[objectId]);
		}
	}

	const std::unordered_map<unsigned, std::shared_ptr<GameObject>>& ObjectManager::GetObjects() const
	{
		return gameObjects;
	}

	ObjectManager::~ObjectManager()
	{
	}
}