////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file System.h															 
/// @date 1/23/2016  2:49 PM			 
/// @author Anshul Soni <soni.anshul93@gmail.com>								 
///																				 
/// As a condition of your accessing this Engine, you agree to be bound 		 
///	by the following terms and conditions: 										 
/// The software was created by Anshul Soni, and all copyright and other 		 
///	rights in such is owned by Anshul Soni. While you are allowed to access,  	 
/// download and use the code for non-commercial, home use you hereby expressly  
/// agree that you will not otherwise copy, distribute, modify, the code. 		 
////////////////////////////////////////////////////////////////////////////////////
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