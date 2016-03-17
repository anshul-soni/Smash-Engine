////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file WindowSystem.h															 
/// @date 1/27/2016  10:59 PM			 
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