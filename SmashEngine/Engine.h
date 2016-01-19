#pragma once
#include <unordered_map>
#include "System.h"


namespace SmashEngine
{
	class Engine
	{
	public:
		Engine(){};
		virtual void Update(float dt)=0;
		virtual void Init()=0;
		virtual  ~Engine(){};
	private:
	};
}