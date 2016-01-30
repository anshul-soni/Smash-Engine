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
