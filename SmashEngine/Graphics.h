////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file Graphics.h															 
/// @date 1/29/2016  5:32 PM			 
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
#include "Engine.h"
#include "SignalHandler.h"
#include "DebugSignal.h"

namespace SmashEngine
{
	class Graphics:public Engine,
		public SignalHandler<DebugSignal>
	{
	public:
		Graphics();
		void Update(float dt)override;
		void Init()override;
		void OnSignal(DebugSignal signal)override;
		EngineType GetType()const override;
		~Graphics();
	private:
		const EngineType type;
		bool debugDraw;
	};
}
