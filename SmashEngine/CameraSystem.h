////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file CameraSystem.h															 
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
#include "System.h"
#include "SignalHandler.h"
#include "CameraSignal.h"

namespace SmashEngine
{
	class CameraSystem :public System,
		public SignalHandler<CameraSignal>
	{
	public:
		static CameraSystem& GetInstance();
		void Init()override;
		void Update(float dt)override;
		void Release()override;
		void OnSignal(CameraSignal signal)override;
		SystemType GetType()const override;
		const glm::mat4& GetViewMatrix()const;
		const glm::mat4& GetProjectionMatrix()const;
	private:
		const SystemType type;
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
		CameraSystem();
		CameraSystem(const CameraSystem&) = delete;
		CameraSystem& operator=(const CameraSystem&) = delete;
	};
}
