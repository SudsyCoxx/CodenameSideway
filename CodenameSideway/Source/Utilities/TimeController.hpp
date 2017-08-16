#pragma once

#include <windows.h>

#include "Timer.hpp"

namespace Utilities {
	class TimeController {
	public:
		TimeController() {}
		
		const int GetUpdatesPerSecond() { return m_totalRefreshInLastInterval; }

		void Update() {
			++m_totalRefreshInInterval;

			// Prevent Too Frequent Updates
			while (m_stopWatch.ElapsedMs() - m_prevUpdateTime < m_refreshRateMS) {
				Sleep((DWORD)(m_refreshRateMS - (m_stopWatch.ElapsedMs() - m_prevUpdateTime)));
			}
			m_prevUpdateTime = m_stopWatch.ElapsedMs();

			if (m_stopWatch.ElapsedMs() >= 1000) {
				m_totalRefreshInLastInterval = m_totalRefreshInInterval;
				m_totalRefreshInInterval = 0;
				m_stopWatch.Reset();
				m_prevUpdateTime = m_stopWatch.ElapsedMs();
			}
		}

		void Start() {
			SetUpdatesPerSecond(m_refreshPerSec);
			m_totalRefreshInInterval = 0;
			m_stopWatch.Reset();
			m_prevUpdateTime = m_stopWatch.ElapsedMs();
		}

		void SetUpdatesPerSecond(int RefreshRate) {
			if (RefreshRate <= 0) return;
			m_refreshPerSec = RefreshRate;
			m_refreshRateMS = 1000 / float(RefreshRate);
		}

	private:
		Stopwatch m_stopWatch;
		int m_refreshPerSec = 60;
		int m_totalRefreshInInterval = 0;
		int m_totalRefreshInLastInterval = 0;
		double m_refreshRateMS = 1000 / 60.f;
		long m_prevUpdateTime = 0;

	protected:
	};
}