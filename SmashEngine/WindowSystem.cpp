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
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			SignalManager::GetInstance().Signal(ENGINE_TERMINATE);
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_W &&  action == GLFW_REPEAT)
		{
			SignalManager::GetInstance().Signal(CAMERA_UP);
		}
		if (key == GLFW_KEY_A &&  action == GLFW_REPEAT)
		{
			SignalManager::GetInstance().Signal(CAMERA_LEFT);
		}
		if (key == GLFW_KEY_S &&  action == GLFW_REPEAT)
		{
			SignalManager::GetInstance().Signal(CAMERA_DOWN);
		}
		if (key == GLFW_KEY_D &&  action == GLFW_REPEAT)
		{
			SignalManager::GetInstance().Signal(CAMERA_RIGHT);
		}
		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
			SignalManager::GetInstance().Signal(DEBUG_TOOGLE);
		}
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		{
			SignalManager::GetInstance().Signal(DEBUG_TOOGLE_PLAY);
		}
		if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS|| action == GLFW_REPEAT))
		{
			SignalManager::GetInstance().Signal(DEBUG_FORWARD);
		}
		if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			SignalManager::GetInstance().Signal(DEBUG_REVERSE);
		}
	}


	void WindowSystem::MouseCallBack(GLFWwindow* window, int button, int action, int mods)
	{
	}

}
