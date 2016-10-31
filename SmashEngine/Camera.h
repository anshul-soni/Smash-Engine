////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Camera.h															 
/// @date 1/29/2016  5:32 PM			 
/// @author Anshul Soni <soni.anshul93@gmail.com>								 
///																				 
/// As a condition of your accessing this Engine, you agree to be bound 		 
///	by the following terms and conditions: 										 
/// The software was created by Anshul Soni, and all copyright and other 		 
///	rights in such is owned by Anshul Soni. While you are allowed to access,  	 
/// download and use the code for non-commercial, home use you hereby expressly  
/// agree that you will not otherwise copy, distribute, modify, the code. 		 
////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "SignalHandler.h"
#include "CameraSignal.h"
#include "Component.h"

namespace SmashEngine
{
	class Camera :public Component,
		public SignalHandler<CameraSignal>
	{
	public:
		Camera();
		void Initialize()override;
		void Deserialize(tinyxml2::XMLElement* pElement)override;
		void Update(float dt)override;
		void Destroy()override;
		void OnSignal(CameraSignal signal)override;
		const glm::mat4& GetViewMatrix()const;
		const glm::mat4& GetProjectionMatrix()const;
	private:
		float fov;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::vec3 position;
		float horizontalAngle;
		float verticalAngle;
		float cameraSpeed;
		float deltaTime;
		glm::vec3 right;
		glm::vec3 up;
		glm::vec3 direction;
		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;
	};
}
//Add layer to camera, to be able to render objects on different
//layers and have multiple cameras.