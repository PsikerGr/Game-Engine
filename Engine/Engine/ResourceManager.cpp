#include <memory>
#include <mutex>
#include <assert.h>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "ResourceManager.h"
#include "ParserOBJ.h"
#include "Texture.h"
#include "GameObject.h"
#include "LogDebug\ILogger.h"

namespace resource
{

	ResourceManager::ResourceManager()
	{
		core::ILogger::LogMessage("Create RessourceManager at : ", __FILE__, __LINE__);
	}

	resource::ResourceManager::~ResourceManager()
	{
		core::ILogger::LogMessage("Delete RessourceManager at : ", __FILE__, __LINE__);

		_gameObjectMap.clear();
	}

	GameObject* ResourceManager::LoadOBJ(const char* objFilename, const char* mtlFileName)
	{
		assert(objFilename != NULL);

		return ParserOBJ::GetInstance().ParseOBJ(objFilename, mtlFileName);
	}

	ResourceManager& resource::ResourceManager::GetInstance()
	{
		static std::unique_ptr<ResourceManager> instance;
		static std::once_flag once_flag;

		std::call_once(once_flag, [] (void)
		{
			instance.reset(new ResourceManager());
		});

		return *instance.get();
	}

	const std::unordered_map<std::string, GameObject*>& ResourceManager::GetGameObjectMap() const
	{
		return _gameObjectMap;
	}

	void ResourceManager::AddGameObject(std::string name, GameObject* gameObject)
	{
		_gameObjectMap.insert(std::make_pair(name, gameObject));
	}

	

}