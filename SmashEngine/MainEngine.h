#pragma once
#include <unordered_map>
#include "Engine.h"


namespace SmashEngine
{
	class MainEngine :public Engine
	{
	public:
		MainEngine();
		void Update(float dt) override;
		void Init()override;
		void InsertSystem(System* system);
		~MainEngine();
	private:
		bool running;
		std::unordered_map<SystemType, System*> systems;
	};
}