////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file MainEngine.cpp															 
/// @date 2/1/2016  1:39 PM			 
/// @author Anshul Soni <soni.anshul93@gmail.com>								 
///																				 
/// As a condition of your accessing this Engine, you agree to be bound 		 
///	by the following terms and conditions: 										 
/// The software was created by Anshul Soni, and all copyright and other 		 
///	rights in such is owned by Anshul Soni. While you are allowed to access,  	 
/// download and use the code for non-commercial, home use you hereby expressly  
/// agree that you will not otherwise copy, distribute, modify, the code. 		 
////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MainEngine.h"
#include "Watch.h"
#include "WindowSystem.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "GameLogicSystem.h"
#include "SignalManager.h"

namespace SmashEngine
{
	MainEngine::MainEngine() :type(ENGINE_Main),running(true)
	{
		SignalManager::GetInstance().Connect<EngineStateSignal>(this);
	}

	void MainEngine::Update(float dt)
	{
		Watch watch = Watch::GetInstance();
		while (running)
		{
			//Update watch system before hte engine 
			watch.Update();
			float deltaTime = watch.Getdt();
			//Update All the engines present in the engine container
			for (auto engine : engines)
			{
				engine.second->Update(deltaTime);
			}
			ObjectManager::GetInstance().Update(deltaTime);
			//Update Singleton systems
			editorSystem->Update(deltaTime);
			gameLogicSystem->Update(deltaTime);
			//ObjectFactory::GetInstance().Update(Watch::GetInstance().Getdt());
			//GameLogicSystem::GetInstance().Update(Watch::GetInstance().Getdt());
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
		Watch::Start();
        editorSystem = std::make_unique<EditorSystem>();
		editorSystem->Init();
        gameLogicSystem = std::make_unique<GameLogicSystem>();
		gameLogicSystem->Init();
		//ObjectFactory::GetInstance().Init();
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
