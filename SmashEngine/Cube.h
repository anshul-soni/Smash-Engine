#pragma once
#include "Primitive.h"
#include "VertexBufferObject.h"

namespace SmashEngine
{
	class Cube :public Primitive
	{
	public:
								Cube();
		bool					Init()override;
		void					Render()override;
		void					BindVAO()const override;
		Shader&					GetShader()override;
		void					SetShader(const std::string& shader)override;
								~Cube();
	private:
		bool					bLoaded;
		Shader*					shader;
		unsigned int			vao;
		VertexBufferObject*		vbo;
	};
}