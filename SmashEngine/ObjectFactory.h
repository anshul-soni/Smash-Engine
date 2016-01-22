#pragma once
#include "ComponentCreator.h"
#include "System.h"
#include "GameObject.h"
#include "Component.h"
namespace SmashEngine
{
	class ComponentCreator;
	class GameObjectFactory :
		public System
	{
	public:
		static GameObjectFactory& GetInstance();
		void Init()override;
		void Update(float dt)override;
		SystemType GetType()const override;
		GameObject* Create(const char* filename);
		void AddComponentCreator(const std::string& name, ComponentCreator* creator);
		void Release()override;
		~GameObjectFactory(void);
	private:
		const SystemType type;
		unsigned int lastObjectId;
		std::unordered_map<std::string, ComponentCreator*> ComponentMap;
		GameObjectFactory(void);
	};
}
