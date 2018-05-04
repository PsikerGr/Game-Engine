#include "../LogDebug/LoggerDebug.h"
#include <Windows.h>

namespace core {

	void LoggerDebug::Write(const std::string& message)
	{
		OutputDebugString((message + "\n").c_str());
	}

}