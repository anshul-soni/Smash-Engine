#pragma once
#include <unordered_map>
#include <sstream>
#include "sigslot.h"
#include "SignalHandler.h"

namespace SmashEngine {
	// Central  used to broadcast signals to other interested components.
	class SignalManager {
	public:
		// Singleton: public accessor.
		static SignalManager& GetInstance();

		// Connects a handler to a broadcast channel.
		template <typename T>
		void Connect(SignalHandler<T>* handler) {
			// Get the channel which corresponds to the template type.
			sigslot::signal1<T>* channel = GetChannel<T>();
			if (channel) {
				// Plug the handler into the channel.
				channel->connect(handler, &SignalHandler<T>::OnSignal);
			} else {
				// If the template does not have a mapping channel, log error and return.
				std::stringstream message;
				message << "Missing channel for " << typeid(T).name();
				Logger::GetInstance().Error(message.str());
			}
		}

		// Sends a signal through a broadcast channel.
		template <typename T>
		void Signal(T signal) {
			// Get the channel which corresponds to the template type.
			sigslot::signal1<T>* channel = GetChannel<T>();
			if (channel) {
				// Send the signal.
				channel->emit(signal);
			} else {
				// If the template does not have a mapping channel, log error and return.
				std::stringstream message;
				message << "Missing channel for " << typeid(T).name();
				Logger::GetInstance().Error(message.str());
			}
		}

	private:
		// Broadcast channels.
		std::unordered_map<size_t, void*> channels;

		// Creates a channel for a given signal type.
		template <typename T>
		void CreateChannel() {
			if (HasChannel<T>()) {
				// The channel already exists, log a warning.
				std::stringstream message;
				message << "Channel for " << typeid(T).name() << " has already been created";
				std::cout << message;
			} else {
				// The channel does not exist. Creating a new one.
				channels[typeid(T).hash_code()] = new sigslot::signal1<T>();
			}
		}

		// Returns whether a signal type has a channel.
		template <typename T>
		bool HasChannel() {
			// Test whether the signal type has a matching channel.
			return channels.find(typeid(T).hash_code()) != channels.end();
		}

		// Retrieves the channel for a given signal type.
		template <typename T>
		sigslot::signal1<T>* GetChannel() {
			// Get the channel which corresponds to the template type.
			return HasChannel<T>() ? static_cast<sigslot::signal1<T>*>(channels[typeid(T).hash_code()]) : nullptr;
		}

		// Singleton: private constructor.
		SignalManager();

		// Singleton: private destructor.
		~SignalManager();

		// Singleton: copy constructor not implemented.
		SignalManager(const SignalManager&) = delete;

		// Singleton: assignment operator not implemented.
		SignalManager& operator=(const SignalManager&) = delete;
	};
}
