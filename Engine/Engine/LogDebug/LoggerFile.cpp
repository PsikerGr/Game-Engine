#include "../LogDebug/LoggerFile.h"
#include "../LogDebug/Exceptions.h"
#include <assert.h>


namespace core {

	LoggerFile::LoggerFile(const std::string& fileName) :
		_fileName(fileName)
	{
		m_File.open(_fileName, std::fstream::out);
		if (!m_File)
			throw LoadingFailed(fileName, "No acces !");

		m_File << " ==================================================== " << std::endl;
		m_File << " ============ Starting Event Log ==================== " << std::endl;
		m_File << " ======= Starting at : " << CurrentTimeDate() << " ==========" << std::endl;
		m_File << " ==================================================== " << std::endl;
		m_File << std::endl;

		m_File.close();
	}

	LoggerFile::~LoggerFile()
	{
		m_File.open(_fileName, std::fstream::out | std::fstream::app);

		m_File << std::endl;
		m_File << " ==================================================== " << std::endl;
		m_File << " =============== Close Event Log ==================== " << std::endl;
		m_File << " ========= Close at : " << CurrentTimeDate() << " ===========" << std::endl;
		m_File << " ==================================================== " << std::endl;

		m_File.close();
	}

	void LoggerFile::Write(const std::string& message)
	{
		m_File.open(_fileName, std::fstream::out | std::fstream::app);

		m_File << message;
		m_File.close();
	}
}