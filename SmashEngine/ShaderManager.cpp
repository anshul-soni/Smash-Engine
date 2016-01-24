#include "stdafx.h"
#include "ShaderManager.h"

namespace SmashEngine
{
	ShaderManager::ShaderManager()
	{
	}

	Shader* ShaderManager::GetShader(const std::string& key)
	{
		if (shaders.find(key) == shaders.end())
		{
			AddShader(key);
		}
		return shaders[key];
	}

	void ShaderManager::AddShader(const std::string& key)
	{
		shaders[key] = new Shader(key);
	}

	ShaderManager::~ShaderManager()
	{
	}
}
