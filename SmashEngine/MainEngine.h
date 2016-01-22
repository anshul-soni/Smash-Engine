#pragma once
#include "Engine.h"
#include "System.h"


namespace SmashEngine
{
	class MainEngine :public Engine
	{
	public:
		MainEngine();
		void Update(float dt) override;
		void Init()override;
		void InsertSystem(System* system);
		void InsertEngine(Engine* engine);
		EngineType GetType()const override;
		~MainEngine();
	private:
		const EngineType type;
		bool running;
		std::unordered_map<SystemType, System*> systems;
		std::unordered_map<EngineType, Engine*> engines;
	};
}
