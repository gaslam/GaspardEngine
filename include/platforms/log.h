#pragma once
#include <deque>
namespace GaspardEngine {
	class LogManager {
	public:
		LogManager() = default;
		enum LogType : int {
			Info,
			Warning,
			Error
		};

		void Init(const std::wstring& name);

		void Log(const wchar_t* message,const LogType& type);
		void LogError(const wchar_t* message);
		void LogWarning(const wchar_t* message);
		void LogInfo(const wchar_t* message);
		void LogToScreen(const wchar_t* message,const LogType& type);
		void LogToFile(const wchar_t* message,const LogType& type);
		void LogInternal(const wchar_t* message,const LogType& type);
	private:
		std::wstring m_LogName{};

		static constexpr size_t m_MaxLogs{ 100 };
		std::deque<std::wstring> m_Logs{};

		_NODISCARD std::wstringstream FormatString(const wchar_t* message, const LogType& type) const;
	};
}
