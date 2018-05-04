#pragma once
#include <iostream>
#include <sstream>

namespace core {

	class DebugException : public std::exception
	{
	public:
		virtual ~DebugException();
		DebugException(const std::string& message = "");

	protected:
		std::string m_Message;
	};

	struct LoadingFailed : public DebugException
	{
		LoadingFailed(const std::string& file, const std::string& message);
	};

}