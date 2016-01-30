#include "stdafx.h"
#include "MainEngine.h"
#include "WatchSystem.h"
#include "WindowSystem.h"
#include "ObjectManager.h"
#include "CameraSystem.h"
#include "ObjectFactory.h"
#include "GameLogicSystem.h"
#include "SignalManager.h"
#include "EditorSystem.h"

namespace SmashEngine
{
	MainEngine::MainEngine() :type(ENGINE_Main),running(true)
	{
		SignalManager::GetInstance().Connect<EngineStateSignal>(this);
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
			//Update Singleton systems
			WindowSystem::GetInstance().Update(WatchSystem::GetInstance().Getdt());
			CameraSystem::GetInstance().Update(WatchSystem::GetInstance().Getdt());
			ObjectFactory::GetInstance().Update(WatchSystem::GetInstance().Getdt());
			ObjectManager::GetInstance().Update(WatchSystem::GetInstance().Getdt());
			//EditorSystem::GetInstance().Update(WatchSystem::GetInstance().Getdt());
			GameLogicSystem::GetInstance().Update(WatchSystem::GetInstance().Getdt());
		}
	}

	void MainEngine::Init()
	{
		//Intialize all the engines first.
		for (auto engine : engines)
		{
			engine.second->Init();
		}
		//Initialize Singleton systems
		WatchSystem::GetInstance().Init();
		WindowSystem::GetInstance().Init();
		CameraSystem::GetInstance().Init();
		ObjectFactory::GetInstance().Init();
		ObjectManager::GetInstance().Init();
		//EditorSystem::GetInstance().Init();
		GameLogicSystem::GetInstance().Init();
	}

	void MainEngine::InsertEngine(Engine* engine)
	{
		engines[engine->GetType()] = engine;
	}

	void MainEngine::OnSignal(EngineStateSignal signal)
	{
		if(signal==EngineStateSignal::ENGINE_TERMINATE)
		{
			running = false;
		}
	}

	EngineType MainEngine::GetType() const
	{
		return type;
	}

	MainEngine::~MainEngine()
	{
	}
}
