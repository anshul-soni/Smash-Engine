#include "stdafx.h"
#include "Primitive.h"
#include "ShaderManager.h"

namespace SmashEngine
{
	Primitive::Primitive():
		bLoaded(false),
		vao(0)
	{
		vbo = new VertexBufferObject();
	}

	void Primitive::BindVAO() const
	{
		glBindVertexArray(vao); 
	}

	Shader & Primitive::GetShader()
	{
		return *shader; 
	}

	void Primitive::SetShader(const std::string& shader)
	{
		this->shader = ShaderManager::GetInstance().GetShader(shader);
	}
}