#pragma once

#include "../LogDebug/ILogger.h"
#include <fstream>

namespace core {

	class LoggerFile : public ILogger
	{
	public:
		LoggerFile(const std::string& fileName = "Output.log");

	private:
		~LoggerFile();
		virtual void Write(const std::string& message);

		std::ofstream m_File;
		std::string _fileName;
	};
}
