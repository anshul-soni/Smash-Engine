////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file WatchSystem.h															 
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
		int GetFrameRate()const;
	private:
		const SystemType type;
		float dt;
		int frameRate;
		int frameCounter;
		double lastTime;
		double lastFrame;
		WatchSystem();
		WatchSystem(const WatchSystem&) = delete;
		WatchSystem& operator=(const WatchSystem) = delete;
	};
}