#pragma once
#include "System.h"

namespace SmashEngine
{
	class WindowSystem:public System
	{
	public:
		WindowSystem();
		void Init()override;
		void Update(float dt)override;
		void Release()override;
		SystemType GetType()const override;
		~WindowSystem();
	private:
		const SystemType type;
		GLFWwindow* window;
		WindowSystem(WindowSystem&) = delete;
		WindowSystem& operator=(const WindowSystem) = delete;


	};
}