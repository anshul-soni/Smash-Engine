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
