#include "stdafx.h"
#include "ObjectFactory.h"
#include "ObjectManager.h"
#include "SystemType.h"

namespace SmashEngine
{
	GameObjectFactory::GameObjectFactory() :type(SYSTEM_Factory), lastObjectId(0)
	{
	}

	void GameObjectFactory::Init()
	{
	}

	void GameObjectFactory::Update(float dt)
	{
	}

	GameObject* GameObjectFactory::Create(const char* filename)
	{
		tinyxml2::XMLDocument xmlDoc;
		std::string gameObjectName;
		assert(!xmlDoc.LoadFile(filename));							//Because XML Error returns 0 on (Success/No Error)
		auto pRoot = xmlDoc.FirstChildElement("GameObject");
		assert(pRoot != nullptr);
		auto pComponent = pRoot->FirstChildElement("Component");
		assert(pComponent != nullptr);
		gameObjectName = pRoot->Attribute("ObjectName");
		auto object = new GameObject(gameObjectName,++lastObjectId);
		while (pComponent != nullptr)
		{
			assert(pComponent != nullptr);
			std::string componentName;
			componentName = pComponent->Attribute("type");
			auto itr = ComponentMap.find(componentName);
			//Abort if the component creator was not found //Component needs to be registered in the factory before creating
			assert(itr != ComponentMap.end());
			//Creator for each object is stored in the map, if the creator was found, then get the creator
			auto creator = itr->second;
			//Create the component that needs to be added to the object using the creator
			auto component = creator->Create();

			component->Deserialize(pComponent);
			object->AddComponent(creator->TypeId, component);
			pComponent = pComponent->NextSiblingElement("Component");
		}
		//GameObject To hold Components 
		ObjectManager::GetInstance().AddObject(object);
		return object;
	}

	SystemType GameObjectFactory::GetType()const
	{
		return type;
	}
	GameObjectFactory::~GameObjectFactory()
	{
		
	}
}