////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Render.cpp															 
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
#include "Render.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "ShapeManager.h"
#include "Camera.h"

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
		if (pElement->FirstChildElement("model"))
		{
			drawableComponent = ModelManager::GetInstance().GetModel(pElement->FirstChildElement("model")->GetText());
		}
		if (pElement->FirstChildElement("shape"))
		{
			drawableComponent = ShapeManager::GetInstance().GetShape(pElement->FirstChildElement("shape")->GetText());
		}
		if (pElement->FirstChildElement("shader"))
		{
			drawableComponent->SetShader(pElement->FirstChildElement("shader")->GetText());
		}
	}

	void Render::Draw(const glm::mat4& projectionMatrix,const glm::mat4& viewMatrix)
	{
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = projectionMatrix*viewMatrix;
		drawableComponent->BindVAO();
		auto shader = drawableComponent->GetShader();
		auto matrixID = glGetUniformLocation(shader.Program, "MVP");
		auto viewMatrixID = glGetUniformLocation(shader.Program, "V");
		auto modelMatrixID = glGetUniformLocation(shader.Program, "M");
		shader.Use();
		auto transformComponent = this->GetOwner()->has(Transform);
		auto transformMatrix = glm::translate(glm::mat4(), transformComponent->GetPosition());
		auto rotationX = glm::rotate(glm::mat4(), transformComponent->GetRotation().x, glm::vec3(1, 0, 0));
		auto rotationY = glm::rotate(glm::mat4(), transformComponent->GetRotation().y, glm::vec3(0, 1, 0));
		auto rotationZ = glm::rotate(glm::mat4(), transformComponent->GetRotation().z, glm::vec3(0, 0, 1));
		auto scale = glm::scale(glm::mat4(), transformComponent->GetScale());
		Model = transformMatrix*rotationX*rotationY*rotationZ*scale;
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
		drawableComponent->Render();

	}

	void Render::Destroy()
	{
	}

	Render::~Render()
	{
	}
}
