#pragma once
#include "System.h"

namespace SmashEngine
{
	class WindowSystem:public System
	{
	public:
		static WindowSystem& GetInstance();
		void Init()override;
		void Update(float dt)override;
		void Release()override;
		SystemType GetType()const override;
		GLFWwindow* GetWindow()const;
		~WindowSystem();
	private:
		WindowSystem();
		const SystemType type;
		GLFWwindow* window;
		WindowSystem(WindowSystem&) = delete;
		WindowSystem& operator=(const WindowSystem) = delete;
	};
}