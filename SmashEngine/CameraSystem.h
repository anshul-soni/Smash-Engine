#pragma once
#include "System.h"

namespace SmashEngine
{
	class CameraSystem :public System
	{
	public:
		static CameraSystem& GetInstance()
		{
			static CameraSystem instance;
			return instance;
		}
		CameraSystem();
		void Init()override;
		void Update(float dt)override;
		void Release()override;
		SystemType GetType()const override;
		const glm::mat4& GetViewMatrix()const;
		const glm::mat4& GetProjectionMatrix()const;
	private:
		const SystemType type;
		float fov;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::vec3 position;
		glm::vec3 rotation;
		CameraSystem(const CameraSystem&) = delete;
		CameraSystem& operator=(const CameraSystem&) = delete;
	};
}