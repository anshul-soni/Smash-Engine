#pragma once
#include "System.h"
#include "GameObject.h"

namespace SmashEngine
{
	class ObjectManager :
		public System
	{
	public:
		static ObjectManager& GetInstance();
		void Init()override;
		void Update(float dt)override;
		void Release()override;
		void AddObject(GameObject* object);
		void DeleteObject(GameObject* object);
		void DeleteObject(const std::string objectName);
		void DeleteObject(const unsigned int objectId);
		SystemType GetType()const override;
		~ObjectManager(void);
	private:
		const SystemType type;
		std::unordered_map<unsigned, GameObject*> GameObjects;
		std::set<GameObject*> ObjectsToBeDeleted;
		ObjectManager(void);
	};
}