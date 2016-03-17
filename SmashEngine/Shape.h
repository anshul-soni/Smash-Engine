////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Shape.h															 
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
