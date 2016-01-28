#pragma once
#include "sigslot.h"

namespace SmashEngine {
	template <typename T>
	class SignalHandler : public sigslot::has_slots<> {
	public:
		virtual void OnSignal(T signal) = 0;

		// Virtual destructor, required for inheritance.
		virtual ~SignalHandler() {}
	};
}
