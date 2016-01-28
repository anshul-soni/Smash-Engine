#pragma once
#include "Engine.h"
#include "SignalHandler.h"
#include "EngineState.h"


namespace SmashEngine
{
	class MainEngine :public Engine,
		public SignalHandler<EngineStateSignal>
	{
	public:
		MainEngine();
		void Update(float dt) override;
		void Init()override;
		void InsertEngine(Engine* engine);
		void OnSignal(EngineStateSignal signal)override;
		EngineType GetType()const override;
		~MainEngine();
	private:
		const EngineType type;
		bool running;
		std::unordered_map<EngineType, Engine*> engines;
	};
}
