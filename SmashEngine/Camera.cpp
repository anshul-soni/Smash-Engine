////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Camera.cpp															 
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
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "SignalManager.h"

namespace SmashEngine
{
	Camera::Camera() :
		fov(45.0f),
		projectionMatrix(glm::mat4(1)),
		viewMatrix(glm::mat4(1)),
		position(glm::vec3(0, 0, 5)),
		cameraSpeed(5.0f),
		deltaTime(0),
		right(glm::vec3(1)),
		up(glm::vec3(1)),
		direction(glm::vec3(1)),
		horizontalAngle(3.14f),
		verticalAngle(0.0f)
	{
	}

	void Camera::Initialize()
	{
		SignalManager::GetInstance().Connect<CameraSignal>(this);
	}

	void Camera::Deserialize(tinyxml2::XMLElement* pElement)
	{
		//layer for the camera will be deserialized
	}

	void Camera::Update(float dt)
	{
		Transform* transformComponent = GetOwner()->has(Transform);
		if (transformComponent)
		{
			float verticalAngle = transformComponent->GetRotation().y;
			float horizontalAngle = transformComponent->GetRotation().x;
			deltaTime = dt;

			direction = glm::vec3(cos(verticalAngle)*sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle)*cos(horizontalAngle));

			right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));

			up = glm::cross(right, direction);

			projectionMatrix = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 1000.0f);

			viewMatrix = glm::lookAt(transformComponent->GetPosition(), transformComponent->GetPosition() + direction, glm::vec3(0, 1, 0));
		}
	}

	void Camera::Destroy()
	{
	}

	void Camera::OnSignal(CameraSignal signal)
	{
		Transform* transformComponent = GetOwner()->has(Transform);
		if (transformComponent)
		{
			glm::vec3 currentPosition = transformComponent->GetPosition();
			glm::vec3 currentOrientation = transformComponent->GetRotation();
			switch (signal)
			{
			case CAMERA_DOWN:
				currentPosition -= up*deltaTime*cameraSpeed;
				break;
			case CAMERA_UP:
				currentPosition += up*deltaTime*cameraSpeed;
				break;
			case CAMERA_LEFT:
				currentPosition -= right*deltaTime*cameraSpeed;
				break;
			case CAMERA_RIGHT:
				currentPosition += right*deltaTime*cameraSpeed;
				break;
			case CAMERA_ZOOMIN:
				currentPosition += direction*deltaTime*(cameraSpeed * 4);
				break;
			case CAMERA_ZOOMOUT:
				currentPosition -= direction*deltaTime*(cameraSpeed * 4);
				break;
			case CAMERA_ROTATE_LEFT:
				currentOrientation.x += deltaTime*cameraSpeed / 5;
				break;
			case CAMERA_ROTATE_RIGHT:
				currentOrientation.x -= deltaTime*cameraSpeed / 5;
				break;
			case CAMERA_ROTATE_UP:
				currentOrientation.y += deltaTime*cameraSpeed / 5;
				break;
			case CAMERA_ROTATE_DOWN:
				currentOrientation.y -= deltaTime*cameraSpeed / 5;
				break;
			default:
				break;
			}
			transformComponent->SetPosition(currentPosition);
			transformComponent->SetRotation(currentOrientation);
		}
	}


	const glm::mat4& Camera::GetViewMatrix()const
	{
		return viewMatrix;
	}

	const glm::mat4& Camera::GetProjectionMatrix()const
	{
		return projectionMatrix;
	}
}
