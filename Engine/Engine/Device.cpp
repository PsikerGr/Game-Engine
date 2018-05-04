#include "GL\glew.h"
#include "GL\freeglut.h"
#include "Device.h"
#include "LogDebug/ILogger.h"
#include "LogDebug/LoggerFile.h"
#include "LogDebug\LoggerDebug.h"
#include "ResourceManager.h"
#include "Wrapper\SFML\AbstractRender.h"
#include "Event\Event.hpp"
#include "Inputs\InputsManager.h"
#include "Inputs\E_InputsType.h"
#include "GameObject.h"





namespace renderer
{
	Device::Device()
	{
		core::ILogger::LogMessage("Create Device at : ", __FILE__, __LINE__);
	}

	Device::~Device()
	{
		core::ILogger::LogMessage("Delete Device at : ", __FILE__, __LINE__);
	}


	void Device::Initialize()
	{
		AbstractRender::CreateRenderWindow(_width, _height, "Lonely Wolf Engine");
		
		resource::ResourceManager::GetInstance().LoadOBJ("Resources/Obj/ORBC/ORBC.obj", "Resources/Obj/ORBC/ORBC.mtl");
	}
	
	void Device::Run()
	{
		AbstractRender::Run();
	}


}