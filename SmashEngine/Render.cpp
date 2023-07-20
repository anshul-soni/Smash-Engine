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
#include "PrimitiveManager.h"
#include "Transform.h"
#include "GameObject.h"
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
		//Set the primitive component
		if (pElement->FirstChildElement("model"))
		{
			primitiveComponent = PrimitiveManager::GetInstance().GetModel(pElement->FirstChildElement("model")->GetText());
		}

		if (pElement->FirstChildElement("primitive"))
		{
			primitiveComponent = PrimitiveManager::GetInstance().GetPrimitive(pElement->FirstChildElement("primitive")->GetText());
		}

		//Set the shader for the component
		if (primitiveComponent)
		{
			if (pElement->FirstChildElement("shader"))
			{
				primitiveComponent->SetShader(pElement->FirstChildElement("shader")->GetText());
			}
		}
	}

	void Render::Draw(const glm::mat4& projectionMatrix,const glm::mat4& viewMatrix)
	{
		glMatrixMode(GL_PROJECTION);
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = projectionMatrix*viewMatrix;
		glm::vec3 lightPosition = glm::vec3(0.0f, 2.0f, -10.0f);
		primitiveComponent->BindVAO();
		Shader shader = primitiveComponent->GetShader();
		GLint matrixID = glGetUniformLocation(shader.Program, "MVP");
		GLint viewMatrixID = glGetUniformLocation(shader.Program, "V");
		GLint modelMatrixID = glGetUniformLocation(shader.Program, "M");
		GLint lightPositionID = glGetUniformLocation(shader.Program, "lightPosition_worldSpace");
		shader.Use();
		std::shared_ptr<Transform> transformComponent = this->GetOwner()->has(Transform);
		glm::mat4 transformMatrix = glm::translate(glm::mat4(), transformComponent->GetPosition());
		glm::mat4 rotationX = glm::rotate(glm::mat4(), transformComponent->GetRotation().x, glm::vec3(1, 0, 0));
		glm::mat4 rotationY = glm::rotate(glm::mat4(), transformComponent->GetRotation().y, glm::vec3(0, 1, 0));
		glm::mat4 rotationZ = glm::rotate(glm::mat4(), transformComponent->GetRotation().z, glm::vec3(0, 0, 1));
		glm::mat4 scale = glm::scale(glm::mat4(), transformComponent->GetScale());
		Model = transformMatrix*rotationX*rotationY*rotationZ*scale;
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniform3fv(lightPositionID,1, &lightPosition[0]);
		primitiveComponent->Render();

	}

	void Render::Destroy()
	{
	}

	Render::~Render()
	{
	}
}
