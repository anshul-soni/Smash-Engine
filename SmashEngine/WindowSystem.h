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
		static void MouseCallBack(GLFWwindow* window, int button, int action, int mods);
		static void KeyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
		WindowSystem(WindowSystem&) = delete;
		WindowSystem& operator=(const WindowSystem) = delete;
	};
}