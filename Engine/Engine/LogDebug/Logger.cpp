#include "Logger.h"

namespace core
{
	void LoggerFile::Write(const std::string& message)
	{
		m_File << message;
	}

	void LoggerDebug::Write(const std::string& message)
	{
		std::cout << message << '\n' << std::endl;
		//OutputDebugString((message + '\n').c_str());
	}

}