#include "stdafx.h"
#include "MainEngine.h"

namespace SmashEngine
{
	MainEngine::MainEngine() :running(true)
	{
	}

	void MainEngine::Update(float dt)
	{
		while (running)
		{
			for (auto system : systems)
			{
				system.second->Update(dt);
			}
		}
	}

	void MainEngine::Init()
	{
		for (auto system : systems)
		{
			system.second->Init();
		}
	}

	void MainEngine::InsertSystem(System* system)
	{
		systems[system->GetType()] = system;
	}

	MainEngine::~MainEngine()
	{
	}
}