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
		for (auto object : GameObjects)
		{
			object.second->Update(dt);
		}
		for (auto object : ObjectsToBeDeleted)
		{
			//make sure that the object exists and was not already deleted
			if(GameObjects.find(object->GetId())!=GameObjects.end())
			{
				auto id = object->GetId();
				delete object;
				GameObjects.erase(id);
			}
		}
		ObjectsToBeDeleted.clear();
	}

	void ObjectManager::Release()
	{
	}

	void ObjectManager::AddObject(GameObject* object)
	{
		GameObjects[object->GetId()] = object;
	}

	void ObjectManager::DeleteObject(GameObject* object)
	{
		if (GameObjects.find(object->GetId())!=GameObjects.end())
		{
			ObjectsToBeDeleted.insert(GameObjects[object->GetId()]);
		}
	}

	void ObjectManager::DeleteObject(const std::string objectName)
	{
		for (auto object:GameObjects)
		{
			if (object.second->GetName()==objectName)
			{
				ObjectsToBeDeleted.insert(object.second);
			}
		}
	}

	void ObjectManager::DeleteObject(const unsigned objectId)
	{
		if (GameObjects.find(objectId) != GameObjects.end())
		{
			ObjectsToBeDeleted.insert(GameObjects[objectId]);
		}
	}

	SystemType ObjectManager::GetType() const
	{
		return type;
	}

	ObjectManager::~ObjectManager()
	{
	}
}