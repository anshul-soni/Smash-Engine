////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file GameLogicSystem.cpp															 
/// @date 1/29/2016  5:32 PM			 
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
#include "GameLogicSystem.h"
#include "ComponentCreator.h"
#include "Transform.h"
#include "Render.h"
#include "Body.h"
#include "Camera.h"

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
		RegisterComponent(Camera);
		ObjectFactory::GetInstance().Create("camera");
		ObjectFactory::GetInstance().Create("test");
		ObjectFactory::GetInstance().Create("cube");
		ObjectFactory::GetInstance().Create("wireframe");
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
