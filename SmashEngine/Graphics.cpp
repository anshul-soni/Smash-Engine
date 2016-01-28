#include "stdafx.h"
#include "Graphics.h"
#include "WindowSystem.h"

namespace SmashEngine
{
	Graphics::Graphics() :type(ENGINE_Graphics)
	{

	}

	void Graphics::Update(float dt)
	{
		glfwSwapBuffers(WindowSystem::GetInstance().GetWindow());
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Graphics::Init()
	{
	}

	EngineType Graphics::GetType() const
	{
		return type;
	}

	Graphics::~Graphics()
	{
	}
}
