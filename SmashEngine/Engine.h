#pragma once
#include "EngineType.h"


namespace SmashEngine
{
	class Engine
	{
	public:
		Engine(){};
		virtual void Update(float dt)=0;
		virtual void Init()=0;
		virtual EngineType GetType()const=0;
		virtual  ~Engine(){};
	private:
	};
}