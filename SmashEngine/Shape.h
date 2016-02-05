#pragma once
#include "Drawable.h"
#include "VertexBufferObject.h"

namespace SmashEngine
{
	enum Shapes{Cube,Sphere,Hemisphere};

	class Shape:public Drawable
	{
	public:
		explicit Shape(const std::string shape);
		bool LoadModel()override;
		void Render()override;
		void BindVAO()const override;
		Shader& GetShader()override;
		void SetShader(const std::string&)override;
		~Shape();
	private:
		Shapes key;
		bool bLoaded;
		VertexBufferObject* vboModelData;
		unsigned int VAO;
		Shader* shader;
		GLuint	vboVertices;
		GLuint 	vboColors;
		GLuint	iboElements;
	};
}
