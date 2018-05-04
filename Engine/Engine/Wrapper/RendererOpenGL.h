#pragma once



#include "RHI.h"
#include "../Camera.h"
#include "../../Common/GLShader.h"

namespace resource
{
	class Mesh;
}

class Skybox;

namespace renderer
{
	class RendererOpenGL : public RHI
	{
	public:
		RendererOpenGL();
		~RendererOpenGL();


	protected:

		/*Create a new Object
		@vertexSize = number of element in vertice array
		@vertexBuff = object vertices array
		@indicesSize = number of element in indices array
		@indidesBuff = object indices array
		*/
		virtual void CoreCreateMesh(resource::GameObject* newGameObject, const uint32_t vertexSize, float* vertexBuff, const uint32_t indicesSize, uint32_t* indiceBuff) override;
	
		/*Load a texture with OpenGL
		 @loadMode = Load mode for different texture format (STBI/DDS)
		 @path = texture path
		 @model = apply texture on the model passed in parametrers
		 */
		virtual void CoreLoadTexture(std::string path, resource::GameObject* gameObject) override;

		/*Load Shader with OpenGL (by default, base.vs and base.fs)
		@mesh = the mesh to apply shader
		@vertexShaderPath = vertex shader path
		@fragmentShaderPath = fragment shader path
		@geometryShaderPath = geometry shader path, not necessary (if there's no geometry shader)
		*/
		virtual void CoreRegisterShader(resource::GameObject* gameObject, const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath) override;

		/*
		Create a Camera
		*/
		virtual void CoreRegisterCamera() override;

		/*Create FrameBuffer 
		@width = width of the screen
		@height = height of the screen
		*/
		virtual bool CoreCreateFrameBuffer(int width, int height) override;

		/*
		Create Skybox
		*/
		virtual void CoreRegisterSkybox() override;

		/*Draw mesh
		@mesh = mesh to draw
		*/
		virtual void CoreDrawGameObject(resource::GameObject* gameObject) override;

		/*
		Return the current Camera
		*/
		virtual component::Camera* CoreGetCamera() override;
	
		/*
		Return the current Skybox
		*/
		virtual Skybox* CoreGetSkybox() override;

		/*Update camera's buffers
		@deltatime = current time for update camera
		*/
		virtual void CoreUpdateBuffersCamera() override;
	
		/*Initialize Skybox's values
		@texSkybox = texture to initialize
		*/
		void InitializeSkybox(uint32_t texSkybox);
		
		/*
		Initialize core render
		*/
		void CoreInitialize() override;
		
		/*
		Initialize Post Process
		*/
		void CorePreparePostProcess() override;
		
		/*
		Post Process render
		*/
		void CorePostProcess() override;

		/*
		Unbind all mesh attributes
		*/
		void CoreUnbind() override;

		/*
		Bind mesh attributes
		*/
		void CoreBindAttrib() override;

		/*
		Render a render quad
		*/
		void RenderQuad();

		/*
		Create and render a grid
		*/
		void RenderGrid(int numberOfLines);

		/*
		Create a render quad (front buffer)
		*/
		void CreateRenderQuad();
		
		/*
		Pre operation for CoreLoadTexture, define load mode, texture path and the mesh to apply texture
		@loadMode = Texture loading mode (STBI, DDS, ...)
		@path = texture path
		@mesh = mesh to apply texture
		*/
		void LoadTexture(resource::LoadMode loadMode, std::string path, resource::Mesh* mesh);

		/*
		Function contain in LoadTexture function, Load the texture with only DDS extension
		@path = DDS texture path
		@mesh = mesh to apply DDS texture
		*/
		void STBILoad(std::string path, resource::Mesh* mesh);

		/*
		Function contains in LoadTexture function, Load all texture except DDS extension
		@path = texture path
		@mesh = mesh to apply texture
		*/
		void DDSLoad(std::string path, resource::Mesh* mesh);

		/*
		Load Cube Map
		@faces = cube map faces
		@texSkybox = skybox texture
		*/
		uint32_t LoadCubeMap(std::vector<const char*> faces, uint32_t texSkybox);

		void CoreSendMatrixToShader(Maths::Mat4 matrix, const char* uniformVariableName) override;

		void UpdateDeltaTime();


		struct BlockIndex
		{
			uint32_t UBO[2]; //UBO[0] = matrices, UBO[1] = materials
		} BlockIndex;
		

	private:
		component::Camera* _cam;
		component::BlockCamera _blockCamera;

		float _deltaTime;
		float _lastFrame;
		
		resource::LoadMode _loadMode;

		GLShader _program;
		GLShader _skyboxProgram;
		uint32_t _FBO;
		uint32_t _depthFBO;
		uint32_t _texFBO;
		uint32_t _quadVAO;
		uint32_t _materialUBO;
		GLShader hdrShader;

		

	};
}