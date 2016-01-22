#pragma once
#include "ComponentCreator.h"
#include "System.h"
#include "GameObject.h"
#include "Component.h"
namespace SmashEngine
{
	class GameObjectFactory :
		public System
	{
	public:
		GameObjectFactory(void);
		void Init()override;
		void Update(float dt)override;
		SystemType GetType()const override;
		GameObject* Create(const char* filename);
		void AddComponentCreator(const std::string& name, ComponentCreator* creator);
		~GameObjectFactory(void);
	private:
		const SystemType type;
		unsigned int lastObjectId;
		std::unordered_map<std::string, ComponentCreator*> ComponentMap;
	};
}
