#include "stdafx.h"
#include "Physics.h"
#include "Body.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "SignalManager.h"

namespace SmashEngine
{
	Physics::Physics() :
		type(ENGINE_Physics), 
		fixedDt(0.01f), 
		debugDt(fixedDt), 
		gravity(10), 
		damping(0.99f), 
		state(PHYSICS_PLAY)
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
			auto gravitationalForce = glm::vec3(0, -gravity*bodyComponent->GetMass(), 0);
			//accumulate the total force
			auto force = gravitationalForce + bodyComponent->GetForce();
			auto a = force*(1 / bodyComponent->GetMass());;
			auto position = transformComponent->GetPosition() + bodyComponent->GetVelocity()*debugDt;
			auto velocity = bodyComponent->GetVelocity() + a*debugDt;
			velocity = velocity*damping;
			transformComponent->SetPosition(position);
			bodyComponent->SetVelocity(velocity);
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
	}
}
