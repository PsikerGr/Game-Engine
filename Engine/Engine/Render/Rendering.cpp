#include <memory>
#include <mutex>

#include "Rendering.h"
#include "../ResourceManager.h"
#include "../Wrapper\RHI.h"
#include "../Mesh.h"
#include "../GameObject.h"
#include "../Material.h"
#include "../Inputs/InputsManager.h"

namespace renderer
{
	void Rendering::CoreCreateMesh(resource::GameObject* newGameObject, const uint32_t vertexSize, float* vertexBuff, const uint32_t indicesSize, uint32_t* indiceBuff, std::string name, std::string texture)
	{
		RHI::CreateMesh(newGameObject, vertexSize, vertexBuff, indicesSize, indiceBuff);
		RHI::RegisterShader(newGameObject, "Shaders/base.vs", "Shaders/base.fs", nullptr);
		
		RHI::LoadTexture(texture, newGameObject);
		RHI::BindAttrib();
		RHI::Unbind();
	
		resource::ResourceManager::GetInstance().AddGameObject(name, newGameObject);
	}

	void Rendering::CoreRenderMeshes()
	{
		auto gameObjecthMap = resource::ResourceManager::GetInstance().GetGameObjectMap();

		for (auto gameObject : gameObjecthMap)
		{
			RHI::DrawGameObject(gameObject.second);
		}
	}

	void Rendering::CoreRender(float deltaTime)
	{
		RHI::PreparePostProcess();
		RHI::UpdateBuffersCamera();
		CoreRenderMeshes();
		InputsManager::GetInstance().Check();
		RHI::PostProcess();
	}

	void Rendering::CoreInitializeRender(int width, int height)
	{
		RHI::RegisterCamera();

		RHI::CreateFrameBuffer(width, height);
	}

	Rendering& Rendering::GetInstance()
	{
		static std::unique_ptr<Rendering> instance;
		static std::once_flag once_flag;

		std::call_once(once_flag, [](void)
		{
			instance.reset(new Rendering());
		});

		return *instance.get();
	}


}