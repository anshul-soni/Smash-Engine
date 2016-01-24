#include "stdafx.h"
#include "MainEngine.h"
#include "WatchSystem.h"
#include "WindowSystem.h"

namespace SmashEngine
{
	MainEngine::MainEngine() :type(ENGINE_Main),running(true)
	{
	}

	void MainEngine::Update(float dt)
	{
		while (running)
		{
			//Update watch system before hte engine 
			WatchSystem::GetInstance().Update(dt);
			//Update All the engines present in the engine container
			for (auto engine : engines)
			{
				engine.second->Update(WatchSystem::GetInstance().Getdt());
			}
			//Update Singleton systems as they are not insterted
			//into the systems map

			//Update All the systems present in the system container
			for (auto system : systems)
			{
				system.second->Update(WatchSystem::GetInstance().Getdt());
			}
		}
	}

	void MainEngine::Init()
	{
		//Intialize all the engines first.
		for (auto engine : engines)
		{
			engine.second->Init();
		}
		//Initialize all the systems.
		for (auto system : systems)
		{
			system.second->Init();
		}
		//Initialize Singleton systems as they are not insterted
		//into the systems map
		WatchSystem::GetInstance().Init();
		WindowSystem::GetInstance().Init();
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
