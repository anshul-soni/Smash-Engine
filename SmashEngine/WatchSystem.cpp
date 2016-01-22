#include "stdafx.h"
#include "WatchSystem.h"

namespace SmashEngine
{
	WatchSystem* WatchSystem::instance = nullptr;

	WatchSystem& WatchSystem::GetInstance()
	{
		return *instance;
	}

	WatchSystem::WatchSystem() :type(SYSTEM_Watch), dt(0), frameRate(0), lastTime(0), frameCounter(0)
	{
		if (instance == nullptr)
			instance = this;
	}

	void WatchSystem::Init()
	{
		lastTime = glfwGetTime();
	}

	void WatchSystem::Update(float dt)
	{
		frameCounter++;
		auto currentTime = glfwGetTime();
		dt = static_cast<float>(currentTime - lastTime);
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

	float WatchSystem::Getdt()const
	{
		return dt;
	}

	float WatchSystem::GetFrameRate()const
	{
		return frameRate;
	}
}