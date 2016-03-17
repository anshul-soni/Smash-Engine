////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2015 Anshul Soni, all rights reserved.                        
/// @file SignalManager.cpp															 
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
#include "stdafx.h"
#include "SignalManager.h"
#include "InputSignal.h"
#include "EngineState.h"
#include "CameraSignal.h"
#include "DebugSignal.h"


namespace SmashEngine {
	SignalManager& SignalManager::GetInstance() {
		static SignalManager instance;
		return instance;
	}

	SignalManager::SignalManager() {
		// Sets up supported broadcast channels.
		CreateChannel<InputSignal>();
		CreateChannel<EngineStateSignal>();
		CreateChannel<CameraSignal>();
		CreateChannel<DebugSignal>();
	}

	SignalManager::~SignalManager() {
		// Clean broadcast channels.
		for (std::pair<size_t, void*> channel : channels) {
			delete channel.second;
		}
	}
}
