#include "stdafx.h"
#include "Cube.h"
#include "ShaderManager.h"

namespace SmashEngine
{
	Cube::Cube()
	{
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

		//vertex Data
		vbo->AddData(&aiVector3D(-1.0f,-1.0f,-1.0f), sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f,-1.0f,-1.0f), sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f, 1.0f,-1.0f), sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f,-1.0f), sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f,-1.0f, 1.0f), sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f,-1.0f, 1.0f), sizeof(aiVector3D));
		vbo->AddData(&aiVector3D( 1.0f, 1.0f, 1.0f), sizeof(aiVector3D));
		vbo->AddData(&aiVector3D(-1.0f, 1.0f, 1.0f), sizeof(aiVector3D));

		vbo->BindVBO();
		vbo->UploadDataToGPU(GL_DYNAMIC_DRAW);

		//index data
		indices.push_back(0); indices.push_back(5); indices.push_back(4);
		indices.push_back(5); indices.push_back(0); indices.push_back(1);


		indices.push_back(3); indices.push_back(7); indices.push_back(6);
		indices.push_back(3); indices.push_back(6); indices.push_back(2);


		indices.push_back(7); indices.push_back(4); indices.push_back(6);
		indices.push_back(6); indices.push_back(4); indices.push_back(5);


		indices.push_back(2); indices.push_back(1); indices.push_back(3);
		indices.push_back(3); indices.push_back(1); indices.push_back(0);


		indices.push_back(3); indices.push_back(0); indices.push_back(7);
		indices.push_back(7); indices.push_back(0); indices.push_back(4);


		indices.push_back(6); indices.push_back(5); indices.push_back(2);
		indices.push_back(2); indices.push_back(5); indices.push_back(1);

		glGenBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
		);
	}
	Cube::~Cube()
	{
	}
}