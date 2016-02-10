#include "stdafx.h"
#include "Graphics.h"
#include "WindowSystem.h"
#include "SignalManager.h"
#include "ObjectManager.h"
#include "Render.h"
#include "CameraSystem.h"
#include "ShaderManager.h"
#include "ModelManager.h"

namespace SmashEngine
{
	Graphics::Graphics() :type(ENGINE_Graphics), debugDraw(false), contactSphere(nullptr)
	{
		SignalManager::GetInstance().Connect<DebugSignal>(this);
		SignalManager::GetInstance().Connect<DrawSignal>(this);

		points.push_back(glm::vec3(0));
	}

		
	void Graphics::Update(float dt)
	{
		glfwSwapBuffers(WindowSystem::GetInstance().GetWindow());
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawPoints();
		points.clear();
		DrawLines();
		lines.clear();
		if (debugDraw)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		for (auto object:ObjectManager::GetInstance().GetObjects())
		{
			auto renderComponent = object.second->has(Render);
			if (renderComponent!=nullptr)
			{
				renderComponent->Draw();
			}
		}
	}

	void Graphics::Init()
	{
	}

	void Graphics::OnSignal(DebugSignal signal)
	{
		switch (signal)
		{
		case DEBUG_TOOGLE:
			debugDraw = !debugDraw;
			break;
		default:
			break;
		}
	}

	void Graphics::OnSignal(DrawSignal signal)
	{
		if(signal.IsPoint())
		{
			points.push_back(signal.GetPoint());
		}else
		{
			lines.push_back(signal.GetLine());
		}
	}

	EngineType Graphics::GetType() const
	{
		return type;
	}

	Graphics::~Graphics()
	{
	}

	void Graphics::DrawLines()
	{
	}

	void Graphics::DrawPoints()
	{
		if(contactSphere == nullptr)
		{
			contactSphere = ModelManager::GetInstance().GetModel("sphere.obj");
			contactSphere->SetShader("model");
		}

		if(points.size() > 0 )
		{
			auto rotationX = glm::rotate(glm::mat4(), 0.0f, glm::vec3(1, 0, 0));
			auto rotationZ = glm::rotate(glm::mat4(), 0.0f, glm::vec3(0, 0, 1));
			auto rotationY = glm::rotate(glm::mat4(), 0.0f, glm::vec3(0, 1, 0));
			auto scale = glm::scale(glm::mat4(), glm::vec3(0.1f));
			for(auto point:points)
			{
				auto Projection = CameraSystem::GetInstance().GetProjectionMatrix();
				auto View = CameraSystem::GetInstance().GetViewMatrix();
				auto Model = glm::mat4(1.0f);
				auto MVP = Projection*View;
				contactSphere->BindVAO();
				auto shader = contactSphere->GetShader();
				auto matrixID = glGetUniformLocation(shader.Program, "MVP");
				auto viewMatrixID = glGetUniformLocation(shader.Program, "V");
				auto modelMatrixID = glGetUniformLocation(shader.Program, "M");
				shader.Use();
				auto transformMatrix = glm::translate(glm::mat4(), point);
				Model = transformMatrix*rotationX*rotationY*rotationZ*scale;
				glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &Model[0][0]);
				glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &View[0][0]);
				contactSphere->Render();
			}
		}
	}
}
