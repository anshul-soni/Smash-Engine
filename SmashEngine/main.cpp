////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file main.cpp															 
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
#include "MainEngine.h"
#include "WindowSystem.h"
#include "Graphics.h"
#include "Physics.h"

int main()
{
	float dt = 0;
	//Main Engine that stores all the Engines and Systems
	SmashEngine::MainEngine* engine = new SmashEngine::MainEngine();
	//Create an instance of the graphic engine here
	SmashEngine::Graphics* graphicsEngine = new SmashEngine::Graphics();
	//Insert the graphics engine into the main engine
	engine->InsertEngine(graphicsEngine);

	//Create an instance of the graphic engine here
	SmashEngine::Physics* physicsEngine = new SmashEngine::Physics();
	//Insert the graphics engine into the main engine
	engine->InsertEngine(physicsEngine);

	//Initialize All the Engines and Systems
	engine->Init();
	//Update All the Engines and Systems
	engine->Update(dt);

	return 0;
}
