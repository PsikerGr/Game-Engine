#include <memory>
#include <mutex>
#include "RHI.h"

#include "../Mesh.h"
#include "Shader.h"
#include "../Device.h"
#include "../Camera.h"
#include "../LogDebug/ILogger.h"
#include "../GameObject.h"

#ifdef OPENGL_RENDER
	#include "RendererOpenGL.h"
	typedef renderer::RendererOpenGL InstanciableRHI;
#endif

namespace renderer
{
	RHI::RHI()
	{
		core::ILogger::LogMessage("Create RHI at : ", __FILE__, __LINE__);
	}
	RHI::~RHI()
	{
		core::ILogger::LogMessage("Delete RHI at : ", __FILE__, __LINE__);
	}

	void RHI::LoadTexture(std::string path, resource::GameObject* gameObject)
	{
		GetInstance().CoreLoadTexture(path.c_str(), gameObject);
	}

	void RHI::RegisterShader(resource::GameObject* gameObject, const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath)
	{
		GetInstance().CoreRegisterShader(gameObject, vertexShaderPath, fragmentShaderPath, geometryShaderPath);
	}

	void RHI::CreateMesh(resource::GameObject* newGameObject, const uint32_t vertexSize, float* vertexBuff, const uint32_t indicesSize, uint32_t* indiceBuff)
	{
		GetInstance().CoreCreateMesh(newGameObject, vertexSize, vertexBuff, indicesSize, indiceBuff);
	}

	bool RHI::CreateFrameBuffer(int width, int height)
	{
		return GetInstance().CoreCreateFrameBuffer(width, height);
	}

	void RHI::DrawGameObject(resource::GameObject* gameObject)
	{
		GetInstance().CoreDrawGameObject(gameObject);
	}

	void RHI::RegisterCamera()
	{
		GetInstance().CoreRegisterCamera();
	}

	component::Camera* RHI::GetCamera()
	{
		return GetInstance().CoreGetCamera();
	}

	Skybox* RHI::GetSkybox()
	{
		return GetInstance().CoreGetSkybox();
	}

	void RHI::Initialize()
	{
		GetInstance().CoreInitialize();
	}

	void RHI::PreparePostProcess()
	{
		GetInstance().CorePreparePostProcess();
	}

	void RHI::PostProcess()
	{
		GetInstance().CorePostProcess();
	}

	void RHI::RegisterSkybox()
	{
		GetInstance().CoreRegisterSkybox();
	}

	void RHI::UpdateBuffersCamera()
	{
		GetInstance().CoreUpdateBuffersCamera();
	}

	/*
	Unbind VertexArray, BufferArray and BufferElementArray for the current mesh
	*/
	void RHI::Unbind()
	{
		GetInstance().CoreUnbind();
	}

	/*
	Bind attributes of the mesh to send them to the shader (Position, Normal, Textures Coords) at a certain format (by default 8)
	*/
	void RHI::BindAttrib()
	{
		GetInstance().CoreBindAttrib();
	}

	void RHI::SendMatrixToShader(Maths::Mat4 matrix, const char* uniformVariableName)
	{
		GetInstance().CoreSendMatrixToShader(matrix, uniformVariableName);
	}

	RHI& RHI::GetInstance()
	{
		static std::unique_ptr<RHI> instance;
		static std::once_flag once_flag;

		std::call_once(once_flag, [] (void)
		{
			instance.reset(new InstanciableRHI());
		});

		return *instance.get();
	}
}