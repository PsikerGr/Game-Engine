#include "Texture.h"
#include "LogDebug\ILogger.h"

namespace resource
{
	Texture::Texture()
	{
		core::ILogger::LogMessage("Create Texture at : ", __FILE__, __LINE__);
	}

	Texture::~Texture()
	{
		core::ILogger::LogMessage("Delete Texture at : ", __FILE__, __LINE__);
	}
}