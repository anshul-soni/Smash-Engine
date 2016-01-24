#include "stdafx.h"
#include "Render.h"
#include "ShaderManager.h"

namespace SmashEngine
{
	Render::Render()
	{
	}

	void Render::Initialize()
	{
	}

	void Render::Deserialize(tinyxml2::XMLElement* pElement)
	{

	}

	void Render::Update(float dt)
	{
	}

	void Render::Destroy()
	{
	}

	void Render::SetShader(const std::string & key)
	{
		shader = ShaderManager::GetInstance().GetShader(key);
	}

	Render::~Render()
	{
	}
}
