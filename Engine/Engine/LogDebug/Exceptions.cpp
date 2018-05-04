#include "../LogDebug/Exceptions.h"

namespace core {

	DebugException::DebugException(const std::string& message) :
		m_Message(message)
	{
	}

	DebugException::~DebugException()
	{
	}

	LoadingFailed::LoadingFailed(const std::string& file, const std::string& message)
	{
		std::ostringstream oss;
		oss << "Error in loading of " << file << std::endl << std::endl << message;
	}
}