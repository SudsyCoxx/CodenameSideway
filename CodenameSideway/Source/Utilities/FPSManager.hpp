#pragma once

#include <windows.h>
#include <iostream>

#include "Timer.hpp"
#include "Singleton.hpp"

namespace Utilities {
	class FPSManager : public Singleton<FPSManager> {
		friend class Singleton<FPSManager>;
	public:
		const int GetFPS() { return m_currentFrameCount; }

		void UpdateWindow() {
			++m_currentFrameCount;

			while (m_stopWatch.ElapsedMs() - m_prevUpdateTime < m_FPShz) {
				Sleep((DWORD)(m_FPShz - (m_stopWatch.ElapsedMs() - m_prevUpdateTime)));
			}
			m_prevUpdateTime = m_stopWatch.ElapsedMs();

			if (m_stopWatch.ElapsedMs() >= 1000) {
				std::cout << m_currentFrameCount << "\n";
				m_currentFrameCount = 0;
				m_stopWatch.Reset();
				m_prevUpdateTime = m_stopWatch.ElapsedMs();
			}
		}

		void Start() {
			SetTargetFPS(m_targetFPS);
			m_currentFrameCount = 0;
			m_stopWatch.Reset();
			m_prevUpdateTime = m_stopWatch.ElapsedMs();
		}

		void SetTargetFPS(int fps) {
			if (fps <= 0) return;
			m_targetFPS = fps;
			m_FPShz = 1000 / fps;
		}

	private:
		FPSManager() {}
		FPSManager(const FPSManager& s) = delete;
		FPSManager& operator=(const FPSManager& s) = delete;

		Stopwatch m_stopWatch;
		int m_targetFPS = 120;
		int m_currentFrameCount = 0;
		double m_FPShz = 1000 / 120.f;
		long m_prevUpdateTime = 0;

	protected:
	};
}