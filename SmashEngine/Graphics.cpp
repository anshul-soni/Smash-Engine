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
#include "SignalManager.h"
#include "ObjectManager.h"
#include "Render.h"
#include "Camera.h"

namespace SmashEngine
{
	Graphics::Graphics() :type(ENGINE_Graphics), debugDraw(false)
	{
		SignalManager::GetInstance().Connect<DebugSignal>(this);
	}

	void Graphics::Update(float dt)
	{

		//For Wireframe uncomment next statement
		if (debugDraw)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		//This works because there is only one camera right now
		//needs to be restructred when adding multiple camera system
		std::shared_ptr<Camera> camera = nullptr;
		for (auto object : ObjectManager::GetInstance().GetObjects())
		{
			std::shared_ptr<Camera> cameraComponent = object.second->has(Camera);
			if (cameraComponent!= nullptr)
			{
				cameraComponent->Update(dt);
				camera = cameraComponent;
			}
		}
		for (auto object:ObjectManager::GetInstance().GetObjects())
		{
			if (camera)
			{
				std::shared_ptr<Render> renderComponent = object.second->has(Render);
				if (renderComponent != nullptr)
				{
					renderComponent->Draw(camera->GetProjectionMatrix(), camera->GetViewMatrix());
				}
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
