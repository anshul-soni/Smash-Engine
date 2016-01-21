#pragma once

namespace SmashEngine
{
	class Shader
	{
	public:
		GLuint Program;
		Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);

		void Use()const;
	};
}