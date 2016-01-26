#pragma once
#include "System.h"
#include "GameObject.h"

namespace SmashEngine
{
	class GameLogicSystem :public System
	{
	public:
		static GameLogicSystem& GetInstance()
		{
			static GameLogicSystem instance;
			return instance;
		}
		GameLogicSystem();
		void Init()override;
		void Update(float dt)override;
		void Release()override;
		SystemType GetType()const override;
	private:
		GameObject* test;
		const SystemType type;
		GameLogicSystem(const GameLogicSystem&) = delete;
		GameLogicSystem& operator=(const GameLogicSystem&) = delete;
	};
}
