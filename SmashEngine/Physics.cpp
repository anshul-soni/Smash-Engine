////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Physics.cpp															 
/// @date 2/5/2016  11:27 PM			 
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
		fixedDt(0.001f), 
		debugDt(fixedDt), 
		gravity(glm::vec3(0.0f, -10.0f, 0.0f)),
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
				CalculatePosition(*object.second);
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

	void Physics::CalculatePosition(GameObject& obj)
	{
		if (state != PHYSICS_PAUSE)
		{
			auto transformComponent = obj.has(Transform);
			auto bodyComponent = obj.has(Body);
			//accumulate the total force
			auto a = gravity + bodyComponent->GetForce()*bodyComponent->GetInverseMass();
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
		ImGui::Text("Use Space to Toogle play/pause");
		ImGui::Text("Left arrow key for previous frame(when paused)");
		ImGui::Text("Right arrow key for next frame(when paused)");
		ImGui::Text("Use 1 to toogle debug draw");
		ImGui::End();
	}
}
