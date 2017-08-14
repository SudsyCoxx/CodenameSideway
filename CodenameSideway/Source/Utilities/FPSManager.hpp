#pragma once

#include "Singleton.hpp"
#include "TimeController.hpp"

namespace Utilities {
	class FPSManager : TimeController, public Singleton<FPSManager> {
		friend class Singleton<FPSManager>;
	public:
		const int GetFPS() { return GetUpdatesPerSecond(); }
		void Start() { TimeController::Start(); }
		void SetFPS(int fps) { TimeController::SetUpdatesPerSecond(fps); }
		void UpdateFPS() { TimeController::Update(); }

	private:
		FPSManager() {}
		FPSManager(const FPSManager& s) = delete;
		FPSManager& operator=(const FPSManager& s) = delete;

	protected:
	};
}