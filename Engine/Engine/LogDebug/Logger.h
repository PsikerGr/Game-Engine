#pragma once
#include "ILogger.h"

namespace core {

	class LoggerFile : public ILogger
	{
	public:
		LoggerFile(const std::string& fileName = "Output.log") : m_File(fileName)
		{
		}

	private:
		virtual void Write(const std::string& message);

		std::ofstream m_File;
	};

	class LoggerDebug : public ILogger
	{
		virtual void Write(const std::string& message);
	};

}