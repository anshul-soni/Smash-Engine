#include "stdafx.h"
#include "Physics.h"
#include "Body.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "SignalManager.h"
#include "imgui.h"

namespace SmashEngine
{
	Physics::Physics() :
		type(ENGINE_Physics), 
		fixedDt(0.01f), 
		debugDt(fixedDt), 
		gravity(-10), 
		damping(0.99f), 
		state(PHYSICS_PAUSE)
	{
		SignalManager::GetInstance().Connect<DebugSignal>(this);
	}

	void Physics::Update(float dt)
	{
		for (auto object : ObjectManager::GetInstance().GetObjects())
		{
			auto bodyComponent = object.second->has(Body);
			if (bodyComponent != nullptr)
			{
				//CalculatePosition(*object.second);
				auto transformComponent = object.second->has(Transform);
				bodyComponent->CalculateAuxilaryVariables(transformComponent, debugDt);
			}
		}
	}

	void Physics::OnSignal(DebugSignal signal)
	{
		switch (signal)
		{
		case DEBUG_TOOGLE_PLAY:
			if (state == PHYSICS_PLAY)
			{
				debugDt = 0.0f;
				state = PHYSICS_PAUSE;
			}
			else
			{
				debugDt = fixedDt;
				state = PHYSICS_PLAY;
			}
			break;
		case DEBUG_FORWARD:
			if (state == PHYSICS_PAUSE)
			{
				state = PHYSICS_FORWARD;
				debugDt = fixedDt;
			}
			break;
		case DEBUG_REVERSE:
			if (state == PHYSICS_PAUSE)
			{
				state = PHYSICS_REVERSE;
				debugDt = -fixedDt;
			}
			break;
		default:
			break;
		}
	}

	void Physics::Init()
	{
	}

	EngineType Physics::GetType() const
	{
		return type;
	}

	void Physics::CalculateAuxilaryVariables(GameObject& object)
	{

	}

	void Physics::CalculatePosition(GameObject& obj)
	{
		if (state != PHYSICS_PAUSE)
		{
			auto transformComponent = obj.has(Transform);
			auto bodyComponent = obj.has(Body);
			auto gravitationalForce = glm::vec3(0, gravity*bodyComponent->GetInverseMass(), 0);
			//accumulate the total force
			auto force = gravitationalForce + bodyComponent->GetForce();
			auto a = force*(1 / bodyComponent->GetInverseMass());;
			auto position = transformComponent->GetPosition() + bodyComponent->GetVelocity()*debugDt;
			auto velocity = bodyComponent->GetVelocity() + a*debugDt;
			velocity *= std::pow(damping, debugDt);
			transformComponent->SetPosition(position);
			//Dont set the velocity of the object
			if (state != PHYSICS_FORWARD && state != PHYSICS_REVERSE)
			{
				bodyComponent->SetVelocity(velocity);
			}
		}
		switch (state)
		{
		case PHYSICS_PLAY:
			break;
		case PHYSICS_PAUSE:
			debugDt = 0.0f;
			state = PHYSICS_PAUSE;
			break;
		case PHYSICS_FORWARD:
			debugDt = 0.0f;
			state = PHYSICS_PAUSE;
			break;
		case PHYSICS_REVERSE:
			debugDt = 0.0f;
			state = PHYSICS_PAUSE;
			break;
		}	
		auto draw = true;
		ImGui::Begin("Physics", &draw, ImVec2(350, 350), 0.5);
		ImGui::Text("Use W,A,S and D to move the camera around");
		ImGui::Text("Use Q and E to Rotate the camera");
		ImGui::Text("Use +,- to zoom in/out");
		ImGui::Text("Use Space to Toogle play/pause");
		ImGui::Text("Left arrow key for previous frame(when paused)");
		ImGui::Text("Right arrow key for next frame(when paused)");
		ImGui::Text("Use 1 to toogle debug draw");
		ImGui::InputFloat("Current dt", &debugDt, ImGuiInputTextFlags_ReadOnly);
		ImGui::End();
	}
}
