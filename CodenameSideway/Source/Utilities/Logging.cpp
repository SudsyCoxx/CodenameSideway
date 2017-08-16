#include "Logging.hpp"

#include <windows.h>
#include <sstream>

using namespace Utilities;

Logging::Logging() {
	// Default log location
	m_logFolder = "";

	// Add log level to log info array
	m_logInfo[ID_DEBUG] = std::make_pair("Debug.txt", false);
	m_logInfo[ID_TRACE] = std::make_pair("Trace.txt", false);
	m_logInfo[ID_OTHER] = std::make_pair("Other.txt", false);

	// Destroy logs from previous run
	DestroyLogs();
}

Logging::~Logging() {

}

bool Logging::SetLocation(std::string LogLocation) {
	if (LogLocation.empty() == false) {
		// Check if folder is a valid location
		if (GetFileAttributesA(LogLocation.c_str()) & FILE_ATTRIBUTE_DIRECTORY) {
			m_logFolder = LogLocation;
			if (DestroyLogs() == false) { return false; }
			return CreateLogs();
		}
	}
	return false;
} 

bool Logging::EnableLogLevel(LogLevel Level, bool Enable) {
	// Not a valid log level
	if (Level > ID_OTHER || Level < ID_DEBUG) {
		Log(ID_DEBUG, -1, "Invalid Log Level", "");
		return false;
	}

	//Destroy log and check if log is now enabled after assigning Enable to it
	if (DestroyLog(Level) && (m_logInfo[Level].second = Enable)) {

		//Open file and add default entry to it
		std::stringstream ss;
		ss << "Log Level : " << Level << std::endl;
		return AddEntry(Level, ss.str());
	}

	return false;
}

void Logging::Log(LogLevel Level, int Code, std::string Message, std::string AdditionalMessage) {
	// Not a valid log level
	if (Level > ID_OTHER || Level < ID_DEBUG) {
		Log(ID_DEBUG, -1, "Invalid Log Level", "");
		return;
	}

	// Not Logging
	if (m_logInfo[Level].second == false) { return; }

	std::stringstream ss;
	ss << "\"" << Code << "\" \"" << Message << "\" \"" << AdditionalMessage << "\"\n";

	AddEntry(Level, ss.str());
}

bool Logging::CreateLogs() {
	bool success = true;
	for (int i = 0; i < 3; ++i) {
		if (m_logInfo[i].second == true) {
			std::stringstream ss;
			ss << "Log Level : " << i << std::endl;
			success &= AddEntry(LogLevel(i), ss.str());
		}
	}
	return success;
}

bool Logging::DestroyLogs() {
	bool success = true;
	for (int i = 0; i < 3; ++i) {
		success &= DestroyLog(LogLevel(i));
	}
	return success;
}

bool Logging::DestroyLog(LogLevel Level) {
	std::lock_guard<std::mutex> lock(m_mutex);

	std::stringstream ss;
	ss << m_logFolder << m_logInfo[Level].first;

	_unlink(ss.str().c_str());

	return true;
}

bool Logging::OpenLog(LogLevel Level) {
	if (m_currentLog.is_open()) {
		m_currentLog.close();
	}
	std::string path = m_logFolder + m_logInfo[Level].first;
	m_currentLog.open(path, std::iostream::out | std::iostream::app);
	return m_currentLog.is_open();
}

bool Logging::CloseLog() {
	if (m_currentLog.is_open()) {
		m_currentLog.close();
	}

	return m_currentLog.is_open() == false;
}

bool Logging::AddEntry(LogLevel Level, std::string Message) {
	std::lock_guard<std::mutex> lock(m_mutex);
	if (OpenLog(Level)) {
		m_currentLog << Message;
		return CloseLog();
	}
	return false;
}