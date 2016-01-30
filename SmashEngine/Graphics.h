#pragma once
#include "Engine.h"
#include "SignalHandler.h"
#include "DebugSignal.h"

namespace SmashEngine
{
	class Graphics:public Engine,
		public SignalHandler<DebugSignal>
	{
	public:
		Graphics();
		void Update(float dt)override;
		void Init()override;
		void OnSignal(DebugSignal signal)override;
		EngineType GetType()const override;
		~Graphics();
	private:
		const EngineType type;
		bool debugDraw;
	};
}
