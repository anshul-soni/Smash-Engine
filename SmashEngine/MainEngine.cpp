#include "stdafx.h"
#include "MainEngine.h"
#include "WatchSystem.h"

namespace SmashEngine
{
	MainEngine::MainEngine() :type(ENGINE_Main),running(true)
	{
	}

	void MainEngine::Update(float dt)
	{
		while (running)
		{
			for (auto engine : engines)
			{
				engine.second->Update(WatchSystem::GetInstance().Getdt());
			}
			for (auto system : systems)
			{
				system.second->Update(WatchSystem::GetInstance().Getdt());
			}
		}
	}

	void MainEngine::Init()
	{
		for (auto engine : engines)
		{
			engine.second->Init();
		}
		for (auto system : systems)
		{
			system.second->Init();
		}
	}

	void MainEngine::InsertSystem(System* system)
	{
		systems[system->GetType()] = system;
	}

	void MainEngine::InsertEngine(Engine* engine)
	{
		engines[engine->GetType()] = engine;
	}

	EngineType MainEngine::GetType() const
	{
		return type;
	}

	MainEngine::~MainEngine()
	{
	}
}
