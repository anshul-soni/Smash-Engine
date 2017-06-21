#include "stdafx.h"
#include "Cube.h"
#include "ShaderManager.h"

namespace SmashEngine
{
	Cube::Cube():
		bLoaded(false),
		vao(0)
	{
		vbo = new VertexBufferObject();
		Init();
	}

	bool Cube::Init()
	{
		if (vbo->GetBufferID() == 0)
		{
			vbo->CreateVBO();
		}
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		vbo->AddData(&aiVector3D(-1.0f,-1.0f,-1.0f),sizeof(aiVector3D)); 
		vbo->AddData(&aiVector3D(-1.0f,-1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f, 1.0f),sizeof(aiVector3D)); 
		vbo->AddData(&aiVector3D( 1.0f, 1.0f,-1.0f),sizeof(aiVector3D)); 
		vbo->AddData(&aiVector3D(-1.0f,-1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f,-1.0f),sizeof(aiVector3D)); 
		vbo->AddData(&aiVector3D( 1.0f,-1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f,-1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f,-1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f, 1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f,-1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f,-1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f,-1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f,-1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f,-1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f,-1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f,-1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f,-1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f, 1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f,-1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f, 1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f,-1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f, 1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f,-1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f, 1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f, 1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f, 1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f,-1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f, 1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f, 1.0f),sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f,-1.0f, 1.0f),sizeof(aiVector3D));

		vbo->BindVBO();
		vbo->UploadDataToGPU(GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		return bLoaded = true;
	}

	void Cube::Render()
	{
		if (!bLoaded)
		{
			return;
		}
		glDrawArrays(GL_TRIANGLES, 0, 12*3);
	}
	void Cube::BindVAO() const
	{
		glBindVertexArray(vao);
	}
	Shader & Cube::GetShader()
	{
		return *shader;
	}
	void Cube::SetShader(const std::string & shader)
	{
		this->shader = ShaderManager::GetInstance().GetShader(shader);
	}
	Cube::~Cube()
	{
	}
}