#include "stdafx.h"
#include "Graphics.h"

namespace SmashEngine
{
	Graphics::Graphics() :type(ENGINE_Graphics)
	{
	}

	void Graphics::Update(float dt)
	{
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
