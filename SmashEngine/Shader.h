#pragma once

namespace SmashEngine
{
	class Shader
	{
	public:
		GLuint Program;
		explicit Shader(const std::string& shaderKey);
		void Use()const;
	};
}