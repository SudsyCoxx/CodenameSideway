#pragma once

#include <type_traits>
#include <chrono>

namespace Utilities {
	class Stopwatch {
	public:
		Stopwatch() {
			Reset();
		}

		void Reset() {
			reset_time = clock.now();
		}

		long ElapsedMs() {
			auto longMs = (long)(std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - reset_time)).count();
			return longMs;
		}

		long ElapsedS() {
			auto longS = (long)(std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - reset_time)).count() / 1000;
			return longS;
		}

		long ElapsedM() {
			auto longM = (long)(std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - reset_time)).count() / 60000;
			return longM;
		}

	private:
		std::chrono::high_resolution_clock clock;
		std::chrono::high_resolution_clock::time_point reset_time;
	
	protected:
	};
}