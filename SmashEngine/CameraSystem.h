#pragma once
#include "System.h"
#include "SignalHandler.h"
#include "InputSignal.h"

namespace SmashEngine
{
	class CameraSystem :public System,
		public SignalHandler<InputSignal>
	{
	public:
		static CameraSystem& GetInstance();
		void Init()override;
		void Update(float dt)override;
		void Release()override;
		virtual void OnSignal(InputSignal signal)override;
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
		CameraSystem();
		CameraSystem(const CameraSystem&) = delete;
		CameraSystem& operator=(const CameraSystem&) = delete;
	};
}
