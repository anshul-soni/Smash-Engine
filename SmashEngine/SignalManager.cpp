#include "stdafx.h"
#include "SignalManager.h"
#include "InputSignal.h"


namespace SmashEngine {
	SignalManager& SignalManager::GetInstance() {
		static SignalManager instance;
		return instance;
	}

	SignalManager::SignalManager() {
		// Sets up supported broadcast channels.
		CreateChannel<InputSignal>();
	}

	SignalManager::~SignalManager() {
		// Clean broadcast channels.
		for (std::pair<size_t, void*> channel : channels) {
			delete channel.second;
		}
	}
}
