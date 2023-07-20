#include "stdafx.h"
#include "Sphere.h"

namespace SmashEngine
{
	Sphere::Sphere()
	{
		Init();
	}
	bool Sphere::Init()
	{
		if (vbo->GetBufferID() == 0)
		{
			vbo->CreateVBO();
		}
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		float const R = 1.0f / (float)(latitude - 1);
		float const S = 1.0f / (float)(longitude - 1);

		for (int r = 0; r < latitude; ++r) 
		{
			for (int s = 0; s < longitude; ++s)
			{
				float const y = (float)(sin(-glm::pi<double>()*0.5f + glm::pi<double>()* r * R));
				float const x = (float)(cos(2 * glm::pi<double>() * s * S) * sin(glm::pi<double>() * r * R));
				float const z = (float)(sin(2 * glm::pi<double>() * s * S) * sin(glm::pi<double>() * r * R));

				
				vbo->AddData(&glm::vec3(x, y, z),sizeof(glm::vec3));

				int curRow = r * longitude;
				int nextRow = (r + 1) * longitude;

				indices.push_back(curRow + s);
				indices.push_back(nextRow + s);
				indices.push_back(nextRow + (s + 1));

				indices.push_back(curRow + s);
				indices.push_back(nextRow + (s + 1));
				indices.push_back(curRow + (s + 1));
			}
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
	void Sphere::Render()
	{

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
	}
	Sphere::~Sphere()
	{
	}
}
