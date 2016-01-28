#include "stdafx.h"
#include "Render.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "CameraSystem.h"

namespace SmashEngine
{
	Render::Render()
	{
	}

	void Render::Initialize()
	{
	}

	void Render::Deserialize(tinyxml2::XMLElement* pElement)
	{
		if (pElement->FirstChildElement("shader")->GetText())
			SetShader(pElement->FirstChildElement("shader")->GetText());
		if (pElement->FirstChildElement("model")->GetText())
			SetModel(pElement->FirstChildElement("model")->GetText());
	}

	void Render::Update(float dt)
	{
		auto Projection = CameraSystem::GetInstance().GetProjectionMatrix();
		auto View = CameraSystem::GetInstance().GetViewMatrix();
		auto Model = glm::mat4(1.0f);
		auto MVP = Projection*View;


		//For Wireframe uncomment next statement
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		model->BindVAO();
		auto matrixID = glGetUniformLocation(shader->Program, "MVP");
		auto viewMatrixID = glGetUniformLocation(shader->Program, "V");
		auto modelMatrixID = glGetUniformLocation(shader->Program, "M");
		shader->Use();
		auto transformComponent = this->GetOwner()->has(Transform);
		auto transformMatrix = glm::translate(glm::mat4(), transformComponent->GetPosition());
		auto rotationX = glm::rotate(glm::mat4(), transformComponent->GetRotation().x, glm::vec3(1, 0, 0));
		auto rotationY = glm::rotate(glm::mat4(), transformComponent->GetRotation().y, glm::vec3(0, 1, 0));
		auto rotationZ = glm::rotate(glm::mat4(), transformComponent->GetRotation().z, glm::vec3(0, 0, 1));
		auto scale = glm::scale(glm::mat4(), transformComponent->GetScale());
		Model = transformMatrix*rotationX*rotationY*rotationZ*scale;
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &View[0][0]);
		model->Render(dt);

	}

	void Render::Destroy()
	{
	}

	void Render::SetShader(const std::string & key)
	{
		shader = ShaderManager::GetInstance().GetShader(key);
	}

	void Render::SetModel(const std::string& key)
	{
		model = ModelManager::GetInstance().GetModel(key);
	}

	Render::~Render()
	{
	}
}
