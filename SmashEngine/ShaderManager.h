#pragma once
#include "Shader.h"

namespace SmashEngine
{
	class ShaderManager
	{
	public:
		static ShaderManager& GetInstance()
		{
			static ShaderManager instance;
			return instance;
		}
		ShaderManager();
		Shader* GetShader(const std::string& key);
		~ShaderManager();
	private:
		void AddShader(const std::string& key);
		std::unordered_map<std::string, Shader*> shaders;
	};
}