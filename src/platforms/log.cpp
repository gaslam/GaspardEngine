#include "platforms/log.h"
#if PRODUCTION_BUILD == 0
#include <iostream>
#endif // PRODUCTION_BUILD
#include <chrono>
#include <ctime>
#include <fstream>
#include <filesystem>


namespace GaspardEngine {
	void LogManager::Init(const std::wstring& name)
	{
		m_LogName = name;

		std::stringstream s{};
		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm tm{};
#ifdef _WIN32
		localtime_s(&tm, &time);
#else
		localtime_r(&time, &tm);
#endif
		s << ENGINE_LOGS_FOLDER << "Logs_" << std::put_time(&tm, "%Y_%m_%d") << ".txt";

		m_LogFileDir += s.str();
	}


	void LogManager::Log(const wchar_t* message, const LogType& logType)
	{
#if PRODUCTION_BUILD == 0
		LogToScreen(message, logType);
#endif

		LogInternal(message, logType);
		LogToFile(message, logType);
	}

	void LogManager::LogError(const wchar_t* message)
	{
		Log(message, LogType::Error);
	}

	void LogManager::LogWarning(const wchar_t* message)
	{
		Log(message, LogType::Warning);
	}

	void LogManager::LogInfo(const wchar_t* message)
	{
		Log(message, LogType::Info);
	}

	void LogManager::LogToScreen(const wchar_t* message, const LogType& type)
	{
#pragma region Windows_Colors
#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		WORD originalAttrs = 0;

		if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) {
			originalAttrs = consoleInfo.wAttributes;
		}

		// Set color based on log type
		switch (type) {
		case LogType::Error:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case LogType::Warning:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Yellow
			break;
		case LogType::Info:
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		default:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Magenta
			break;
		}

		// Print the colored message
		std::wcout << FormatString(message, type).str();

		// Restore original color
		SetConsoleTextAttribute(hConsole, originalAttrs);
#else
		std::wcout << FormatString(message, type).str();
#endif
#pragma endregion
	}

	void LogManager::LogToFile(const wchar_t* message, const LogType& type)
	{
		if (!std::filesystem::exists(m_LogFileDir))
		{
			std::wofstream logFile(m_LogFileDir);
			logFile.close();
		}
		std::wofstream logFile(m_LogFileDir, std::ios::app);
		if (logFile.is_open())
		{
			logFile << FormatString(message, type).str();
			logFile.close();
		}
	}

	void LogManager::LogInternal(const wchar_t* message, const LogType& type)
	{
		if (m_MaxLogs <= m_Logs.size())
		{
			m_Logs.pop_back();
		}
		m_Logs.push_front(FormatString(message, type).str());
	}

	std::wstringstream LogManager::FormatString(const wchar_t* message, const LogType& type) const
	{
		std::wstringstream s;
		switch (type) {
		case LogType::Error:   s << L"[error]"; break;
		case LogType::Warning: s << L"[warning]"; break;
		case LogType::Info:    s << L"[info]"; break;
		default:               s << L"[unknown]"; break;
		}
		s << L" - ";

		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm tm{};
#ifdef _WIN32
		localtime_s(&tm, &time);
#else
		localtime_r(&time, &tm);
#endif
		s << L"#" << std::put_time(&tm, L"%Y-%m-%d %X") << L" - ";

		s << message << "\n";

		return s;
	}

}
