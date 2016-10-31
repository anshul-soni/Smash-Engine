////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file MainEngine.h															 
/// @date 1/28/2016  8:45 PM			 
/// @author Anshul Soni <soni.anshul93@gmail.com>								 
///																				 
/// As a condition of your accessing this Engine, you agree to be bound 		 
///	by the following terms and conditions: 										 
/// The software was created by Anshul Soni, and all copyright and other 		 
///	rights in such is owned by Anshul Soni. While you are allowed to access,  	 
/// download and use the code for non-commercial, home use you hereby expressly  
/// agree that you will not otherwise copy, distribute, modify, the code. 		 
////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Engine.h"
#include "SignalHandler.h"
#include "EngineState.h"
#include "EditorSystem.h"
#include "GameLogicSystem.h"

namespace SmashEngine
{
	class MainEngine :public Engine,
		public SignalHandler<EngineStateSignal>
	{
	public:
		MainEngine();
		void Update(float dt) override;
		void Init()override;
		void InsertEngine(Engine* engine);
		void OnSignal(EngineStateSignal signal)override;
		EngineType GetType()const override;
		~MainEngine();
	private:
		const EngineType type;
		bool running;
		std::unordered_map<EngineType, Engine*> engines;
		EditorSystem* editorSystem;
		GameLogicSystem* gameLogicSystem;
	};
}
