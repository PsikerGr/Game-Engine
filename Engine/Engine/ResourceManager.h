#pragma once
#include <unordered_map>
#include "Macro.h"
#include "Mesh.h"

namespace resource
{
	class ParserOBJ;
	class GameObject;

	class ENGINE_DLL ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		GameObject* LoadOBJ(const char* objFilename, const char* mtlFileName);

		static ResourceManager &GetInstance();
		const std::unordered_map<std::string, GameObject*>& GetGameObjectMap() const;
		void AddGameObject(std::string name, GameObject* gameObject);

	private:
		std::unordered_map<std::string, GameObject*> _gameObjectMap;

	};

}
