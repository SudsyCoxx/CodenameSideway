#pragma once

#include <mutex>
#include <fstream>
#include "Singleton.hpp"

namespace Utilities {
	enum LogLevel {
		ID_DEBUG = 0,
		ID_TRACE = 1,
		ID_OTHER = 2
	};
	
	class Logging : public Singleton<Logging> {
		friend class Singleton<Logging>;
	public:
		bool SetLocation(std::string LogLocation);
		bool EnableLogLevel(LogLevel Level, bool Enable);
		void Log(LogLevel Level, int Code, std::string Message, std::string AdditionalMessage);

		~Logging();
	private:
		Logging(const Logging& s) = delete;
		Logging& operator=(const Logging& s) = delete;

		bool CreateLogs();
		bool DestroyLogs();
		bool DestroyLog(LogLevel Level);
		bool OpenLog(LogLevel Level);
		bool CloseLog();
		bool AddEntry(LogLevel Level, std::string Message);

		std::mutex m_mutex;
		std::pair<std::string, bool> m_logInfo[3];
		std::string m_logFolder;

		std::ofstream m_currentLog;

	protected:
		Logging();
	};
}