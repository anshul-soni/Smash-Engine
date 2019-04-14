////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file ObjectFactory.cpp															 
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
		std::string filepath = ResourcePath::GetInstance().GetPath(RESOURCE_Object, filename);
		if(xmlDoc.LoadFile(filepath.c_str())!=tinyxml2::XML_SUCCESS)
		{
			std::cout << "failed to load file " << filepath << std::endl;
			return nullptr;
		}
		tinyxml2::XMLElement* pRoot = xmlDoc.FirstChildElement("GameObject");
		assert(pRoot != nullptr);
		gameObjectName = pRoot->Attribute("name");
		tinyxml2::XMLElement* pComponent = pRoot->FirstChildElement("Component");
		assert(pComponent != nullptr);
		//GameObject To hold Components 
		GameObject* object = new GameObject(gameObjectName,++lastObjectId);
		while (pComponent != nullptr)
		{
			assert(pComponent != nullptr);
			std::string componentName;
			componentName = pComponent->Attribute("type");
			std::unordered_map<std::string,ComponentCreator*>::iterator itr = ComponentMap.find(componentName);
			//Abort if the component creator was not found 
			//Component needs to be registered in the factory before creating
			assert(itr != ComponentMap.end());
			//Creator for each object is stored in the map, if the creator was found, then get the creator
			ComponentCreator* creator = itr->second;
			//Create the component that needs to be added to the object using the creator
			Component* component = creator->Create();
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
