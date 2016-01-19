#pragma once
#include "System.h"

namespace SmashEngine
{
	class WatchSystem:public System
	{
	public:
		static WatchSystem& GetInstance()
		{
			static WatchSystem instance;
			return instance;
		}
		WatchSystem();
		void Init()override;
		void Update(float dt)override;
		void Release()override;
		SystemType GetType()const override;
		float Getdt();
		int GetFrameRate();
	private:
		const SystemType type;
		float dt;
		float frameRate;
		int frameCounter;
		float lastTime;
		WatchSystem(const WatchSystem&) = delete;
		WatchSystem& operator=(const WatchSystem&) = delete;
	};
}