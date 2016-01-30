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
