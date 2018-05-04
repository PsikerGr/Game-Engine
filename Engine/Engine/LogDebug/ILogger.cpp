#include "ILogger.h"
#include <ctime>

namespace core {

	ILogger* ILogger::s_Instance = nullptr;

	ILogger::~ILogger()
	{
	}

	ILogger& ILogger::Log()
	{
		return *s_Instance;
	}

	void ILogger::SetLogger(ILogger* logger)
	{
		Destroy();
		s_Instance = logger;
	}

	void ILogger::Destroy()
	{
		delete s_Instance;
		s_Instance = NULL;
	}

	std::string ILogger::CurrentTimeDate()
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[24];
		localtime_s(&tstruct, &now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}

	std::string ILogger::CurrentFileAndLine(const std::string file, int line)
	{
		std::string fileAndLine;
		std::string str(file);
		fileAndLine = "File : " + std::string(file) + " and line : " + std::to_string(line);

		return fileAndLine;
	}

	void ILogger::LogMessage(std::string message, std::string file, int line)
	{
		std::string fileNameWithourPath = file.substr(file.find_last_of("\\") + 1, file.size());
		core::ILogger::Log() << message << core::ILogger::CurrentTimeDate() << "\n" << core::ILogger::CurrentFileAndLine(fileNameWithourPath, line) << "\n\n";
	}
}