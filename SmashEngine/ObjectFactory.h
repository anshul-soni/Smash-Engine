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
		GameObject* Create(const std::string& filename);
		void AddComponentCreator(const std::string& name, ComponentCreator* creator);
		void Release()override;
		~ObjectFactory(void);
	private:
		const SystemType type;
		unsigned int lastObjectId;
		std::unordered_map<std::string, ComponentCreator*> ComponentMap;
		ObjectFactory(void);
	};
}
