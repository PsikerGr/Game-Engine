#pragma once

#include <stdint.h>
#include <string>

namespace resource
{
	class Mesh;
	class ResourceManager;
	class GameObject;
}

namespace renderer
{
	
	class RHI;

	class Rendering
	{
	public:
		Rendering() = default;
		Rendering(const Rendering&) = delete;
		Rendering(const Rendering&&) = delete;
		~Rendering() = default;

		void CoreCreateMesh(resource::GameObject* newGameObject, const uint32_t vertexSize, float* vertexBuff, const uint32_t indicesSize, uint32_t* indiceBuff, std::string name, std::string texture);
		void CoreRenderMeshes();
		void CoreRender(float deltaTime);

		/*
		Function to initialize render(FrameBuffer, Create a Camera) 
		The function call other function of the RHI
		@ width / height = size of the window to create the framebuffer

		*/
		void CoreInitializeRender(int width, int height); 
		static Rendering& GetInstance();

	private:

	};

	
}