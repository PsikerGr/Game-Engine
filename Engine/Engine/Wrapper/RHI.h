#pragma once

#include "../Texture.h"
#include "../Skybox.h"
#include "Mat4.h"

namespace resource
{

	class Mesh;
	class Shader;
	class GameObject;
}

namespace renderer
{
	class Device;
}

namespace component
{

	class Camera;
}

namespace renderer
{
	class RHI
	{
	public:
		virtual ~RHI();

		
		static void LoadTexture(std::string path, resource::GameObject* gameObject);
		static void RegisterShader(resource::GameObject* gameObject, const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath);
		static void CreateMesh(resource::GameObject* newGameObject, const uint32_t vertexSize, float* vertexBuff, const uint32_t indicesSize, uint32_t* indiceBuff);
		static bool CreateFrameBuffer(int width, int height);
		static void DrawGameObject(resource::GameObject* mesh);
		static void RegisterCamera();
		static void RegisterSkybox();
		static component::Camera* GetCamera();
		static Skybox* GetSkybox();
		static void Initialize();
		static void PreparePostProcess();
		static void PostProcess();
		static void UpdateBuffersCamera();
		static void Unbind();
		static void BindAttrib();
		static void SendMatrixToShader(Maths::Mat4 matrix, const char* uniformVariableName);
		

	protected:
		RHI();

		virtual void CoreCreateMesh(resource::GameObject* newGameObject, const uint32_t vertexSize, float* vertexBuff, const uint32_t indicesSize, uint32_t* indiceBuff) = 0;
		virtual void CoreRegisterShader(resource::GameObject* gameObject, const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath) = 0;
		virtual void CoreLoadTexture(std::string path, resource::GameObject* gameObject) = 0;
		virtual bool CoreCreateFrameBuffer(int width, int height) = 0;
		virtual void CoreRegisterCamera() = 0;
		virtual component::Camera* CoreGetCamera() = 0;
		virtual void CoreRegisterSkybox() = 0;
		virtual void CoreDrawGameObject(resource::GameObject* gameObject) = 0;
		virtual Skybox* CoreGetSkybox() = 0;
		virtual void CoreInitialize() = 0;
		virtual void CorePreparePostProcess() = 0;
		virtual void CorePostProcess() = 0;
		virtual void CoreUpdateBuffersCamera() = 0;
		virtual void CoreUnbind() = 0;
		virtual void CoreBindAttrib() = 0;
		virtual void CoreSendMatrixToShader(Maths::Mat4 matrix, const char* uniformVariableName) = 0;


	private:
		static RHI& GetInstance();

	};

	
}
