#pragma once
#include "System.h"

namespace SmashEngine
{
	class WatchSystem:public System
	{
	public:
		static WatchSystem& GetInstance();
		void Init()override;
		void Update(float dt)override;
		void Release()override;
		SystemType GetType()const override;
		float Getdt()const;
		float GetFrameRate()const;
	private:
		const SystemType type;
		float dt;
		float frameRate;
		int frameCounter;
		double lastTime;
		WatchSystem();
		WatchSystem(const WatchSystem&) = delete;
		WatchSystem& operator=(const WatchSystem) = delete;
	};
}