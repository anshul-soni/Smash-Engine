#include "stdafx.h"
#include "MainEngine.h"
#include "WindowSystem.h"
#include "Graphics.h"
#include "WatchSystem.h"

int main()
{
	float dt = 0;
	//Main Engine that stores all the Engines and Systems
	auto engine = new SmashEngine::MainEngine();
	//Create an instance of the graphic engine here
	auto graphicsEngine = new SmashEngine::Graphics();
	//Insert the graphics engine into the main engine
	engine->InsertEngine(graphicsEngine);
	//Create window system
	auto windowSystem = new SmashEngine::WindowSystem();
	//Insert window system into the main engine
	engine->InsertSystem(windowSystem);
	//Create Watch System
	auto watchSystem =new SmashEngine::WatchSystem();
	//Insert watch System into the main engine
	engine->InsertSystem(watchSystem);
	//Initialize All the Engines and Systems
	engine->Init();
	//Update All the Engines and Systems
	engine->Update(dt);

	return 0;
}
