#include "stdafx.h"
#include "EditorSystem.h"
#include "imgui_impl_glfw_gl3.h"
#include "WindowSystem.h"

namespace SmashEngine
{
	EditorSystem& EditorSystem::GetInstance()
	{
		static EditorSystem instance;
		return instance;
	}

	void EditorSystem::Init()
	{
		ImGui_ImplGlfwGL3_Init(WindowSystem::GetInstance().GetWindow(), true);

		ImGui_ImplGlfwGL3_NewFrame();
	}

	void EditorSystem::Update(float dt)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		ImGui::Render();
		ImGui_ImplGlfwGL3_NewFrame();
	}

	SystemType EditorSystem::GetType() const
	{
		return type;
	}

	void EditorSystem::Release()
	{
	}

	EditorSystem::~EditorSystem()
	{
	}

	EditorSystem::EditorSystem() :type(SYSTEM_Editor)
	{
	}
}
