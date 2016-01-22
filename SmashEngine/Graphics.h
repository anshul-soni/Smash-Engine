#pragma once
#include "Engine.h"

namespace SmashEngine
{
	class Graphics:public Engine
	{
	public:
		Graphics();
		void Update(float dt)override;
		void Init()override;
		EngineType GetType()const override;
		~Graphics();
	private:
		const EngineType type;
	};
}