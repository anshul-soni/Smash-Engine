#include "stdafx.h"
#include "GameLogicSystem.h"
#include "ComponentCreator.h"
#include "Transform.h"
#include "Render.h"
#include "Body.h"
#include "SignalManager.h"
#include "DrawSignal.h"

namespace SmashEngine
{
	GameLogicSystem::GameLogicSystem() :type(SYSTEM_GameLogic)
	{
	}

	void GameLogicSystem::Init()
	{
		//Register all the components in the object factory
		//This creates a component creator for the type of 
		//component you register
		RegisterComponent(Transform);
		RegisterComponent(Render);
		RegisterComponent(Body);
		ObjectFactory::GetInstance().Create("test");
		ObjectFactory::GetInstance().Create("cube");
		ObjectFactory::GetInstance().Create("sphere");
		auto sphere = ObjectFactory::GetInstance().Create("sphere");
		auto sphereBody = sphere->has(Body);
		sphereBody->SetStatic(false);
		auto sphereTransform = sphere->has(Transform);
		sphereTransform->SetPosition(sphereTransform->GetPosition().x, 3.0f, sphereTransform->GetPosition().z);

		sphere = ObjectFactory::GetInstance().Create("sphere");
		sphereTransform = sphere->has(Transform);
		sphereTransform->SetPosition(4.0F, sphereTransform->GetPosition().y, sphereTransform->GetPosition().z);

		sphere = ObjectFactory::GetInstance().Create("cube");
		sphereTransform = sphere->has(Transform);
		sphereTransform->SetPosition(4.0F, 3.0f, sphereTransform->GetPosition().z);
	}

	void GameLogicSystem::Update(float dt)
	{
		//Signal to draw debug points
		//SignalManager::GetInstance().Signal(DrawSignal(glm::vec3(0)));
		//SignalManager::GetInstance().Signal(DrawSignal(glm::vec3(0,1,0), glm::vec3(1)));
	}

	void GameLogicSystem::Release()
	{
	}

	SystemType GameLogicSystem::GetType() const
	{
		return type;
	}
}
