#pragma once
#include "Engine.h"
#include "SignalHandler.h"
#include "DebugSignal.h"
#include "PhysicsState.h"

namespace SmashEngine
{
	class GameObject;

	class Physics:public Engine,
		public SignalHandler<DebugSignal>
	{
	public:
		Physics();
		void Update(float dt)override;
		void OnSignal(DebugSignal signal)override;
		void Init()override;
		EngineType GetType()const override;
	private:
		void CalculatePosition(GameObject& objt);
		const EngineType type;
		float fixedDt;
		float debugDt;
		float gravity;
		float damping;
		PhysicsState state;
	};
}
