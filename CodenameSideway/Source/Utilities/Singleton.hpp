#pragma once

#include <mutex>

namespace Utilities {
	template <typename T>
	class Singleton {
	public:
		static T& GetInstance(){
			// Thread-safe singleton creation
			std::lock_guard<std::mutex> lock(m_mutex);
	
			// Return a static instance of the class
			static T instance;
			return instance;
		}
	
	private:
		std::mutex m_mutex;

		// USAGE : When using singleton, ensure the following 3 functions are marked delete or private at the very least
		// T();
		// T(const T& s) = delete;
		// T& operator=(const T& s) = delete;

	protected:
	};
}