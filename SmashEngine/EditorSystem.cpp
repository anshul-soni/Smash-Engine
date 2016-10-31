////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file EditorSystem.cpp															 
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
#include "EditorSystem.h"
#include "imgui_impl_glfw_gl3.h"
#include "WindowSystem.h"

namespace SmashEngine
{

	EditorSystem::EditorSystem() :WindowSystem(),type(SYSTEM_Editor)
	{
	}

	void EditorSystem::Init()
	{
		WindowSystem::Init();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui_ImplGlfwGL3_NewFrame();
	}

	void EditorSystem::Update(float dt)
	{
		WindowSystem::Update(dt);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		auto draw = true;
		ImGui::Begin("Camera Instructions", &draw, ImVec2(350, 350), 0.5);
		ImGui::Text("Use Scroll Wheell to Zoom in/out");
		ImGui::Text("Press Left Mouse button and move to move the camera");
		ImGui::Text("Press Left Mouse button and move to Rotate the camera");
		ImGui::End();
		ImGui::Render();
		ImGui_ImplGlfwGL3_NewFrame();
	}

	SystemType EditorSystem::GetType() const
	{
		return type;
	}

	void EditorSystem::Release()
	{
		WindowSystem::Release();
	}

	EditorSystem::~EditorSystem()
	{
	}
}
