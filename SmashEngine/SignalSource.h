#pragma once
#include "SignalHandler.h"

namespace SmashEngine {
	template <typename T>
	class SignalSource {
	public:
		virtual void Connect(SignalHandler<T>* handler) = 0;
		virtual void Signal(T signal) = 0;

		// Virtual destructor, required for inheritance.
		virtual ~SignalSource() {}
	};
}
