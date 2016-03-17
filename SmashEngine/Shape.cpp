////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Shape.cpp															 
/// @date 2/5/2016  11:27 PM			 
/// @author Anshul Soni <soni.anshul93@gmail.com>								 
///																				 
/// As a condition of your accessing this Engine, you agree to be bound 		 
///	by the following terms and conditions: 										 
/// The software was created by Anshul Soni, and all copyright and other 		 
///	rights in such is owned by Anshul Soni. While you are allowed to access,  	 
/// download and use the code for non-commercial, home use you hereby expressly  
/// agree that you will not otherwise copy, distribute, modify, the code. 		 
////////////////////////////////////////////////////////////////////////////////////
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
		- 1.0f, -1.0f, -1.0f, // triangle 1 : begin
		- 1.0f, -1.0f, 1.0f,
		- 1.0f, 1.0f, 1.0f, // triangle 1 : end
		    1.0f, 1.0f, -1.0f, // triangle 2 : begin
		- 1.0f, -1.0f, -1.0f,
		- 1.0f, 1.0f, -1.0f, // triangle 2 : end
		     1.0f, -1.0f, 1.0f,
		 - 1.0f, -1.0f, -1.0f,
		     1.0f, -1.0f, -1.0f,
		     1.0f, 1.0f, -1.0f,
		     1.0f, -1.0f, -1.0f,
		 - 1.0f, -1.0f, -1.0f,
		 - 1.0f, -1.0f, -1.0f,
		 - 1.0f, 1.0f, 1.0f,
		 - 1.0f, 1.0f, -1.0f,
		     1.0f, -1.0f, 1.0f,
		 - 1.0f, -1.0f, 1.0f,
		 - 1.0f, -1.0f, -1.0f,
		 - 1.0f, 1.0f, 1.0f,
		 - 1.0f, -1.0f, 1.0f,
		     1.0f, -1.0f, 1.0f,
		     1.0f, 1.0f, 1.0f,
		     1.0f, -1.0f, -1.0f,
		     1.0f, 1.0f, -1.0f,
		     1.0f, -1.0f, -1.0f,
		     1.0f, 1.0f, 1.0f,
		     1.0f, -1.0f, 1.0f,
		     1.0f, 1.0f, 1.0f,
		     1.0f, 1.0f, -1.0f,
		 - 1.0f, 1.0f, -1.0f,
		     1.0f, 1.0f, 1.0f,
		 - 1.0f, 1.0f, -1.0f,
		 - 1.0f, 1.0f, 1.0f,
		     1.0f, 1.0f, 1.0f,
		 - 1.0f, 1.0f, 1.0f,
		     1.0f, -1.0f, 1.0f
		 };
		glGenBuffers(1, &VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		glVertexAttribPointer( 0,3,GL_FLOAT,GL_FALSE,0,static_cast<void*>(nullptr));
		return bLoaded = true;
	}

	void Shape::Render()
	{
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}

	void Shape::BindVAO() const
	{
		
		glBindBuffer(GL_ARRAY_BUFFER, VAO);
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
