#include "stdafx.h"
#include "ObjectFactory.h"
#include "ObjectManager.h"
#include "SystemType.h"
#include "ResourcePath.h"
#include "tinyxml2.h"
namespace SmashEngine
{
	ObjectFactory::ObjectFactory() :type(SYSTEM_ObjectFactory), lastObjectId(0)
	{
	}

	ObjectFactory& ObjectFactory::GetInstance()
	{
		static ObjectFactory instance;
		return instance;
	}

	void ObjectFactory::Init()
	{
	}

	void ObjectFactory::Update(float dt)
	{
	}

	GameObject* ObjectFactory::Create(const std::string& filename)
	{
		tinyxml2::XMLDocument xmlDoc;
		std::string gameObjectName;
		auto filepath = ResourcePath::GetInstance().GetPath(RESOURCE_Object, filename);
		if(xmlDoc.LoadFile(filepath.c_str())!=tinyxml2::XML_SUCCESS)
		{
			std::cout << "failed to load file " << filepath << std::endl;
			return nullptr;
		}
		auto pRoot = xmlDoc.FirstChildElement("GameObject");
		assert(pRoot != nullptr);
		gameObjectName = pRoot->Attribute("name");
		auto pComponent = pRoot->FirstChildElement("Component");
		assert(pComponent != nullptr);
		//GameObject To hold Components 
		auto object = new GameObject(gameObjectName,++lastObjectId);
		while (pComponent != nullptr)
		{
			assert(pComponent != nullptr);
			std::string componentName;
			componentName = pComponent->Attribute("type");
			auto itr = ComponentMap.find(componentName);
			//Abort if the component creator was not found 
			//Component needs to be registered in the factory before creating
			assert(itr != ComponentMap.end());
			//Creator for each object is stored in the map, if the creator was found, then get the creator
			auto creator = itr->second;
			//Create the component that needs to be added to the object using the creator
			auto component = creator->Create();
			//Call the desrializer for the required component
			component->Deserialize(pComponent);
			//add the component that was created to the object
			object->AddComponent(creator->TypeId, component);
			pComponent = pComponent->NextSiblingElement("Component");
		}
		//Pass the object to the object manager
		object->Initialize();
		ObjectManager::GetInstance().AddObject(object);
		//return the pointer to object 
		return object;
	}

	void ObjectFactory::AddComponentCreator(const std::string& name, ComponentCreator* creator)
	{
		ComponentMap[name] = creator;
	}

	void ObjectFactory::Release()
	{
	}

	SystemType ObjectFactory::GetType()const
	{
		return type;
	}

	ObjectFactory::~ObjectFactory()
	{
		
	}
}
