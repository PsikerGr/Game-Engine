#pragma once

#include "../LogDebug/ILogger.h"

namespace core {

	class LoggerDebug : public ILogger
	{
	private:
		virtual void Write(const std::string& message);
	};
}