////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Graphics.cpp															 
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
#include "Graphics.h"
#include "WindowSystem.h"
#include "SignalManager.h"
#include "ObjectManager.h"
#include "Render.h"

namespace SmashEngine
{
	Graphics::Graphics() :type(ENGINE_Graphics), debugDraw(false)
	{
		SignalManager::GetInstance().Connect<DebugSignal>(this);
	}

	void Graphics::Update(float dt)
	{
		glfwSwapBuffers(WindowSystem::GetInstance().GetWindow());
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//For Wireframe uncomment next statement
		if (debugDraw)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		for (auto object:ObjectManager::GetInstance().GetObjects())
		{
			auto renderComponent = object.second->has(Render);
			if (renderComponent!=nullptr)
			{
				renderComponent->Draw();
			}
		}
	}

	void Graphics::Init()
	{
	}

	void Graphics::OnSignal(DebugSignal signal)
	{
		switch (signal)
		{
		case DEBUG_TOOGLE:
			debugDraw = !debugDraw;
			break;
		default:
			break;
		}
	}

	EngineType Graphics::GetType() const
	{
		return type;
	}

	Graphics::~Graphics()
	{
	}

}
