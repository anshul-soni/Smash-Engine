#include "stdafx.h"
#include "CameraSystem.h"
#include "SignalManager.h"

namespace SmashEngine
{
	CameraSystem& CameraSystem::GetInstance()
	{
		static CameraSystem instance;
		return instance;
	}
	CameraSystem::CameraSystem() :
		type(SYSTEM_Camera),
		fov(45.0f),
		projectionMatrix(glm::mat4(1)),
		viewMatrix(glm::mat4(1)),
		position(glm::vec3(0, 0, 5)),
		cameraSpeed(1.0f),
		deltaTime(0),
		right(glm::vec3(1)),
		up(glm::vec3(1)),
		direction(glm::vec3(1)),
		horizontalAngle(3.14f),
		verticalAngle(0.0f)
	{
	}

	void CameraSystem::Init()
	{
		SignalManager::GetInstance().Connect<CameraSignal>(this);
	}

	void CameraSystem::Update(float dt)
	{
		deltaTime = dt;

		direction = glm::vec3(cos(verticalAngle)*sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle)*cos(horizontalAngle));

		right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));

		up = glm::cross(right, direction);

		projectionMatrix = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 1000.0f);

		viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
	}

	void CameraSystem::Release()
	{
	}

	void CameraSystem::OnSignal(CameraSignal signal)
	{
		switch (signal)
		{
		case CAMERA_DOWN:
			position -= up*deltaTime*cameraSpeed;
			break;
		case CAMERA_UP:
			position += up*deltaTime*cameraSpeed;
			break;
		case CAMERA_LEFT:
			position -= right*deltaTime*cameraSpeed;
			break;
		case CAMERA_RIGHT:
			position += right*deltaTime*cameraSpeed;
			break;
		case CAMERA_ZOOMIN:
			position += direction*deltaTime*cameraSpeed;
			break;
		case CAMERA_ZOOMOUT:
			position -= direction*deltaTime*cameraSpeed;
			break;
		default:
			break;
		}
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
