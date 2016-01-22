#include "stdafx.h"
#include "GameLogicSystem.h"

namespace SmashEngine
{
	GameLogicSystem::GameLogicSystem() :type(SYSTEM_GameLogic)
	{
	}

	void GameLogicSystem::Init()
	{
	}

	void GameLogicSystem::Update(float dt)
	{
	}

	void GameLogicSystem::Release()
	{
	}

	SystemType GameLogicSystem::GetType() const
	{
		return type;
	}
}
