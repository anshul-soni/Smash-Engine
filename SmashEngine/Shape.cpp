#include "stdafx.h"
#include "Shape.h"
#include "ShaderManager.h"

namespace SmashEngine
{
	Shape::Shape(const std::string shape)
	{
		if (shape == "Cube")
		{
			key = Shapes::Cube;
		}
		if (shape == "Sphere")
		{
			key = Shapes::Sphere;
		}
		if (shape == "Hemisphere")
		{
			key = Shapes::Hemisphere;
		}
		LoadModel();
	}

	bool Shape::LoadModel()
	{

		static const GLfloat g_vertex_buffer_data[] = {
			-1.0f, -1.0f, -1.0f,
			0.0f, 0.0f, 0.0f,
			-1.0f, 1.0f, 1.0f,
			0.0f, -1.0f, 0.0f,
		};

		// One color for each vertex. They were generated randomly.
		static const GLfloat g_color_buffer_data[] = {
			0.583f, 0.771f, 0.014f,
			0.609f, 0.115f, 0.436f
		};
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer( 0,3,GL_FLOAT,GL_FALSE,0,static_cast<void*>(nullptr));

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));
		return bLoaded = true;
	}

	void Shape::Render()
	{
		glLineWidth(1);
		glDrawArrays(GL_LINE_STRIP, 0, 4); 
	}

	void Shape::BindVAO() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	}

	Shader& Shape::GetShader()
	{
		return *shader;
	}

	void Shape::SetShader(const std::string& shader)
	{
		this->shader = ShaderManager::GetInstance().GetShader(shader);
	}

	Shape::~Shape()
	{
	}
}
