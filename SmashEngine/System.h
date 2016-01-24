#pragma once
#include "SystemType.h"
namespace SmashEngine
{
	enum SystemType;

	//Base class for all the systems
	//Systems are allowed to be singleton if required
	class System
	{
	public:
		//Constructor sets the type of the system
		System(){};
		//Initialize properties of the system
		virtual void Init() = 0;
		//Updates the system
		virtual void Update(float dt) = 0;
		//This is called when the engine is shutting down
		//Responsible for releasing all the acquired
		//resources
		virtual void Release() = 0;
		//Returns the type of the system
		virtual SystemType GetType()const = 0;
		//virtual public destructor 
		virtual ~System(){}
	private:
		//System& operator=(const System&) = delete;
	};
}