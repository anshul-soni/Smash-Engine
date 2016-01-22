#include "stdafx.h"
#include "CameraSystem.h"

namespace SmashEngine
{
	CameraSystem::CameraSystem() :
		type(SYSTEM_Camera),
		fov(45),
		projectionMatrix(glm::mat4(1)),
		viewMatrix(glm::mat4(1)),
		position(glm::vec3(0,0,0))
	{
	}

	void CameraSystem::Init()
	{
	}

	void CameraSystem::Update(float dt)
	{
		glm::vec3 direction(cos(rotation.y)*sin(rotation.x), sin(rotation.y), cos(rotation.y)*cos(rotation.x));

		auto right = glm::vec3(sin(rotation.x - 3.14f / 2.0f), 0, cos(rotation.x - 3.14f / 2.0f));

		auto up = glm::cross(right, direction);

		projectionMatrix = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 1000.0f);

		viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
	}

	void CameraSystem::Release()
	{
	}

	SystemType CameraSystem::GetType() const
	{
		return type;
	}

	const glm::mat4& CameraSystem::GetViewMatrix()const
	{
		return viewMatrix;
	}

	const glm::mat4& CameraSystem::GetProjectionMatrix()const
	{
		return projectionMatrix;
	}
}
