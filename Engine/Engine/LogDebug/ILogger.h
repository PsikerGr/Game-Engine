#pragma once

#include <iostream>
#include <sstream>
#include "../Macro.h"

namespace core {

	class ILogger
	{
	public:
		virtual ~ILogger();

		static void SetLogger(ILogger* logger);
		template <class T> ILogger& operator <<(const T& toLog);

		static void LogMessage(std::string message, std::string file, int line);

	protected:
		static std::string CurrentTimeDate();

	private:
		static ILogger& Log();
		static std::string CurrentFileAndLine(const std::string file, int line);
		static void Destroy();
		virtual void Write(const std::string& message) = 0;
		static ILogger* s_Instance;

	};

	template <class T> ILogger& ILogger::operator <<(const T& toLog)
	{
		std::ostringstream stream;
		stream << toLog;
		//Write(stream.str());

		return Log();
	}
}