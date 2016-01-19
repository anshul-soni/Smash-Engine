#include "stdafx.h"
#include "WatchSystem.h"

namespace SmashEngine
{
	WatchSystem::WatchSystem() :type(SYSTEM_Watch), dt(0), frameRate(0), lastTime(0)
	{
	}

	void WatchSystem::Init()
	{
		lastTime = glfwGetTime();
	}

	void WatchSystem::Update(float dt)
	{
		frameCounter++;
		auto currentTime = glfwGetTime();
		dt = currentTime - lastTime;
		frameRate = 1000.0f/dt;
		lastTime = glfwGetTime();

	}

	void WatchSystem::Release()
	{
	}

	SystemType WatchSystem::GetType() const
	{
		return type;
	}

	float WatchSystem::Getdt()
	{
		return dt;
	}

	int WatchSystem::GetFrameRate()
	{
		return frameRate;
	}
}