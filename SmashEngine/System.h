#pragma once
#include "SystemType.h"
namespace SmashEngine
{
	enum SystemType;

	class System
	{
	public:
		System(){};
		virtual void Init() = 0;
		virtual void Update(float dt) = 0;
		virtual void Release() = 0;
		virtual SystemType GetType()const = 0;
		virtual ~System(){}
	private:
		System(System&)=delete;
		System& operator=(const System&) = delete;
	};
}