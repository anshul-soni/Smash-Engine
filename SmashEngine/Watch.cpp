////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Watch.cpp															 
/// @date 1/23/2016  2:49 PM			 
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
#include "Watch.h"

namespace SmashEngine
{
	Watch* Watch::instance = nullptr;
	Watch::Watch() :dt(0), frameRate(0), frameCounter(0), lastTime(0)
	{
		lastTime = glfwGetTime();
	}

	void Watch::Start()
	{
		if(instance)
		{
			return;
		}
		instance = new Watch();
	}
	
	void Watch::Stop()
	{
		//clear the system
	}

	Watch& Watch::GetInstance()
	{
		if (instance)
		{
			return *instance;
		}
		Start();
		return *instance;
	}

	void Watch::Update()
	{
		frameCounter++;
		auto currentTime = glfwGetTime();
		this->dt = static_cast<float>(currentTime - lastFrame);
		if(currentTime-lastTime >= 1.0)
		{
			frameRate = frameCounter;
			frameCounter = 0;
			lastTime += 1.0;
		}
		lastFrame = currentTime;
	}

	float Watch::Getdt()const
	{
		return dt;
	}

	int Watch::GetFrameRate()const
	{
		return frameRate;
	}
}