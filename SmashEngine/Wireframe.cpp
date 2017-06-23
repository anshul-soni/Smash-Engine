#include "stdafx.h"
#include "WireFrame.h"


namespace SmashEngine
{
	Wireframe::Wireframe()
	{
		Init();
	}

	bool Wireframe::Init()
	{
		if (vbo->GetBufferID() == 0)
		{
			vbo->CreateVBO();
		}
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		for (int i = -size/2; i <= size/2; i++)
		{
			vbo->AddData(&glm::vec3(i, 0, -size/2),sizeof(glm::vec3));
			vbo->AddData(&glm::vec3(i, 0, size/2), sizeof(glm::vec3));
			vbo->AddData(&glm::vec3(-size/2, 0, i), sizeof(glm::vec3));
			vbo->AddData(&glm::vec3(size/2, 0, i), sizeof(glm::vec3));
		}
		//int hl = size / 2;
		//int hw = size / 2;

		//int n = 0;

		//for (int i = -hl; i <= hl; i++)
		//{
		//	vbo->AddData(&glm::vec3(i, 0, -hw),sizeof(glm::vec3));
		//	vbo->AddData(&glm::vec3(i, 0, hw) ,sizeof(glm::vec3));
		//	vbo->AddData(&glm::vec3(-hl, 0, i),sizeof(glm::vec3));
		//	vbo->AddData(&glm::vec3(hl, 0, i) ,sizeof(glm::vec3));
		//}
		for (int i = 0; i < 50*50; i+=4)
		{
			indices.push_back(i);
			indices.push_back(i+1);
			indices.push_back(i+2);
			indices.push_back(i+3);
		}

		vbo->BindVBO();
		vbo->UploadDataToGPU(GL_DYNAMIC_DRAW);

		glGenBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		return true;
	}
	void Wireframe::Render()
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, NULL);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	Wireframe::~Wireframe()
	{
	}
}