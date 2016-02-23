#include "stdafx.h"
#include "Shader.h"
#include "ResourcePath.h"

namespace SmashEngine
{
	Shader::Shader(const std::string& shaderKey)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		auto vertexPath = ResourcePath::GetInstance().GetPath(RESOURCE_VertexShader, shaderKey);
		auto fragmentPath = ResourcePath::GetInstance().GetPath(RESOURCE_FragmentShader, shaderKey);

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try{
			vShaderFile.open(vertexPath.c_str());
			fShaderFile.open(fragmentPath.c_str());

			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << shaderKey << std::endl;
			std::cout << "ERROR::SHADER::FILE_NOT_READ_SUCCESSFULLY" << std::endl;
		}
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, nullptr);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
			std::cout << shaderKey << std::endl;
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED \n" << infoLog << std::endl;
		};

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, nullptr);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
			std::cout << shaderKey << std::endl;
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED \n" << infoLog << std::endl;
		};

		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(Program);

		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Program, 512, nullptr, infoLog);
			std::cout << shaderKey << std::endl;
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED \n" << infoLog << std::endl;

		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Shader::Use()const
	{
		glUseProgram(this->Program);
	}
}
