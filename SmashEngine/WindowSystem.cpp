#include "stdafx.h"
#include "WindowSystem.h"
#include "SignalManager.h"
#include "EngineState.h"
#include "CameraSignal.h"
#include "DebugSignal.h"
namespace SmashEngine
{
	WindowSystem::WindowSystem() :type(SYSTEM_Window), window(nullptr)
	{
	}

	WindowSystem & WindowSystem::GetInstance()
	{
		static WindowSystem instance;
		return instance;
	}

	void WindowSystem::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		auto monitor = glfwGetPrimaryMonitor();
		auto mode = glfwGetVideoMode(monitor);
		this->window = glfwCreateWindow(1024, 768, "Smash Engine", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		if (window == nullptr)
		{
			std::cout << "failed to create window" << std::endl;
			glfwTerminate();
		}
		glfwSetKeyCallback(window, KeyBoardCallBack);
		glfwSetMouseButtonCallback(window, MouseCallBack);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "failed to initialize glew" << std::endl;
		}
		glViewport(0, 0, 1024, 768);
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		glDisable(GL_CULL_FACE);
	}

	void WindowSystem::Update(float dt)
	{
		if (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}else
		{
			SignalManager::GetInstance().Signal(ENGINE_TERMINATE);
		}
	}

	void WindowSystem::Release()
	{
	}

	SystemType WindowSystem::GetType() const
	{
		return type;
	}

	GLFWwindow* WindowSystem::GetWindow()const
	{
		return window;
	}

	WindowSystem::~WindowSystem()
	{
	}
	void WindowSystem::KeyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
	}
	void WindowSystem::MouseCallBack(GLFWwindow* window, int button, int action, int mods)
	{
	}

}
