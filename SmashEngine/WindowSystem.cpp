////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file WindowSystem.cpp															 
/// @date 2/1/2016  1:39 PM			 
/// @author Anshul Soni <soni.anshul93@gmail.com>								 
///																				 
/// As a condition of your accessing this Engine, you agree to be bound 		 
///	by the following terms and conditions: 										 
/// The software was created by Anshul Soni, and all copyright and other 		 
///	rights in such is owned by Anshul Soni. While you are allowed to access,  	 
/// download and use the code for non-commercial, home use you hereby expressly  
/// agree that you will not otherwise copy, distribute, modify, the code. 		 
////////////////////////////////////////////////////////////////////////////////////
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
			glfwSwapBuffers(window);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
			SmashEngine::SignalManager::GetInstance().Signal(SmashEngine::ENGINE_TERMINATE);
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
	void WindowSystem::MouseCallBack(GLFWwindow* window, int button, int action, int mods)
	{
	}

}
