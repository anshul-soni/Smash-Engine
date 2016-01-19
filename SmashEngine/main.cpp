#include "stdafx.h"
#include "MainEngine.h"
#include "WindowSystem.h"

int main()
{
	float dt = 0;
	SmashEngine::MainEngine* engine = new SmashEngine::MainEngine();
	SmashEngine::WindowSystem* window = new SmashEngine::WindowSystem();
	engine->InsertSystem(window);
	engine->Init();
	engine->Update(dt);
	return 0;
}