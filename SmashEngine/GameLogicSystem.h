////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file GameLogicSystem.h															 
/// @date 1/26/2016  7:43 PM			 
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
#include "System.h"
#include "GameObject.h"

namespace SmashEngine
{
	class GameLogicSystem :public System
	{
	public:
		static GameLogicSystem& GetInstance()
		{
			static GameLogicSystem instance;
			return instance;
		}
		GameLogicSystem();
		void Init()override;
		void Update(float dt)override;
		void Release()override;
		SystemType GetType()const override;
	private:
		GameObject* test;
		const SystemType type;
		GameLogicSystem(const GameLogicSystem&) = delete;
		GameLogicSystem& operator=(const GameLogicSystem&) = delete;
	};
}
