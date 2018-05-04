#include "Component.h"
#include "LogDebug\ILogger.h"
#include "Mesh.h"
#include "Material.h"

namespace resource
{
	Component::Component()
	{
		core::ILogger::LogMessage("Create Component at : ", __FILE__, __LINE__);
	}

	Component::Component(std::string name)
	:_name(name)
	{
		core::ILogger::LogMessage("Create Component at : ", __FILE__, __LINE__);
	}

	Component::~Component()
	{
		core::ILogger::LogMessage("Delete Component at : ", __FILE__, __LINE__);
		_name.erase();
	}

	const std::string & Component::GetName() const
	{
		return _name;
	}
	
	
}