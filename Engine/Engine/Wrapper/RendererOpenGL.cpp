#include "RendererOpenGL.h"
#include <cassert>


#define STB_IMAGE_IMPLEMENTATION
#include "../../Libs/stb/stb_image.h"

#include "GL\glew.h"
#include "GL\freeglut.h"

#include "Shader.h"
#include "../ResourceManager.h"
#include "../LogDebug/ILogger.h"
#include "../../MathLib/Tools.h"
#include "../Material.h"



namespace renderer
{
	RendererOpenGL::RendererOpenGL()
	{
		core::ILogger::LogMessage("Create Renderer at : ", __FILE__, __LINE__);
	}

	RendererOpenGL::~RendererOpenGL()
	{
		delete _cam;
		_cam = nullptr;
		_program.Destroy();
		_skyboxProgram.Destroy();
		hdrShader.Destroy();
		//core::ILogger::LogMessage("Delete Renderer at : ", __FILE__, __LINE__);
	}

	void RendererOpenGL::CoreCreateMesh(resource::GameObject* newGameObject, const uint32_t vertexSize, float* vertexBuff, const uint32_t indicesSize, uint32_t* indiceBuff)
	{
		resource::Mesh* gameObjectMesh = nullptr;
		if (newGameObject->HaveComponentOfType<resource::Mesh>())
		{
			gameObjectMesh = newGameObject->GetComponent<resource::Mesh>();
		}

		gameObjectMesh->SetIndices(indiceBuff, indicesSize);
		gameObjectMesh->SetVertices(vertexBuff, vertexSize);
		gameObjectMesh->SetIndicesCount(indicesSize);
	
		glGenVertexArrays(1, &gameObjectMesh->RenderData._VAO);
		glBindVertexArray(gameObjectMesh->RenderData._VAO);

		glGenBuffers(1, &gameObjectMesh->RenderData._VBO);
		glBindBuffer(GL_ARRAY_BUFFER, gameObjectMesh->RenderData._VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(float), vertexBuff, GL_STATIC_DRAW);

		glGenBuffers(1, &gameObjectMesh->RenderData._IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gameObjectMesh->RenderData._IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(uint32_t), indiceBuff, GL_STATIC_DRAW);

		for (GLuint i = 0; i < 2; i++)
		{
			glGenBuffers(1, &BlockIndex.UBO[i]);
			glBindBuffer(GL_UNIFORM_BUFFER, BlockIndex.UBO[i]);
			glBindBufferBase(GL_UNIFORM_BUFFER, i, BlockIndex.UBO[i]);
		}

		component::Transform* gameObjectTransform = newGameObject->GetComponent<component::Transform>();

		Maths::Vec3d scaleVector(1.0f, 1.0f, 1.0f);
		Maths::Mat4 scaleMatrix = gameObjectTransform->ScaleMatrix(scaleVector);
		Maths::Mat4 rotationMatrix = gameObjectTransform->RotationMatrix(Maths::Vec3d(0.f, -20.f, 0.f));

		Maths::Mat4 worldMatrix = gameObjectTransform->WorldMatrix();
	}

	void RendererOpenGL::CoreLoadTexture(std::string path, resource::GameObject* gameObject)
	{
		resource::Mesh* gameObjectMesh = gameObject->GetComponent<resource::Mesh>();

		std::size_t delimiter = path.find(".");

		std::string directory = "Resources/Obj/";

		directory += path;

		if (delimiter != std::string::npos)
		{
			std::string extension = path.substr(delimiter + 1, 4);

			if (extension != "dds")
				_loadMode = resource::STBI;

			else
				_loadMode = resource::DDS;
		}

		LoadTexture(_loadMode, directory, gameObjectMesh);
	}

	void RendererOpenGL::CoreRegisterShader(resource::GameObject* gameObject, const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath)
	{
		resource::Mesh* gameObjectMesh = gameObject->GetComponent<resource::Mesh>();
		resource::Material* meshMaterial = gameObjectMesh->GetMaterial();

		meshMaterial->SetVertexShader(vertexShaderPath);
		_program.LoadShader(GL_VERTEX_SHADER, vertexShaderPath);
		
		if (geometryShaderPath != nullptr)
		{
			meshMaterial->SetGeometryShader(geometryShaderPath);
			_program.LoadShader(GL_GEOMETRY_SHADER, geometryShaderPath);
		}

		meshMaterial->SetFragmentShader(fragmentShaderPath);
		_program.LoadShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

		_program.Create();
	}

	bool RendererOpenGL::CoreCreateFrameBuffer(int width, int height)
	{
		//Creation of the frameBuffer for the back screen render
		glGenFramebuffers(1, &_FBO);

		glGenRenderbuffers(1, &_depthFBO);
		glBindRenderbuffer(GL_RENDERBUFFER, _depthFBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glGenTextures(1, &_texFBO);
		glBindTexture(GL_TEXTURE_2D, _texFBO);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		//GL_FRAMEBUFFER = read/write, GL_READ_FRAMEBUFFER = read only/ GL_DRAW_FRAMEBUFFER = write only
		glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
		// clip the texture as color buffer #0
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texFBO, 0);
		// clip the texture as depth buffer of FBO
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthFBO);
		//Switch to the framebuffer by default (frameBuffer create by GLUT or the render context)
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		assert(status == GL_FRAMEBUFFER_COMPLETE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glClearColor(0.f, 1.0f, 0.0f, 1.0f);

		return true;
	}

	void RendererOpenGL::CoreRegisterCamera()
	{
		_cam = new component::Camera();
		_blockCamera = _cam->GetBlockCamera();
	}

	void RendererOpenGL::CoreDrawGameObject(resource::GameObject* gameObject)
	{
		_program.Bind();

		if (gameObject->HaveComponentOfType<resource::Mesh>() && gameObject != nullptr)
		{
			resource::Mesh* gameObjectMesh = gameObject->GetComponent<resource::Mesh>();
			glBindVertexArray(gameObjectMesh->RenderData._VAO);
			uint32_t textUnit = 0;
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, gameObjectMesh->GetMaterial()->GetTexture()->TextureData._texture);
			int textureLocation = glGetUniformLocation(_program.Get(), "u_Texture");
			glUniform1i(textureLocation, textUnit);
			glBindVertexArray(gameObjectMesh->RenderData._VAO);
			glDrawElements(GL_TRIANGLES, gameObjectMesh->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
		}
		component::Transform* gameObjectTransform = gameObject->GetComponent<component::Transform>();
		CoreSendMatrixToShader(gameObjectTransform->GetWorld(), "world");

		glBindBuffer(GL_UNIFORM_BUFFER, BlockIndex.UBO[0]);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(Maths::Mat4) * 2, _blockCamera._viewMatrix.m, GL_STREAM_DRAW);
		
		_program.Unbind();
		glBindVertexArray(0);
	}

	void RendererOpenGL::CoreUpdateBuffersCamera()
	{
		UpdateDeltaTime();
		_cam->UpdateMatrix(_deltaTime);
		_blockCamera = _cam->GetBlockCamera();
	}

	component::Camera* RendererOpenGL::CoreGetCamera()
	{
		return _cam;
	}

	Skybox* RendererOpenGL::CoreGetSkybox()
	{
		return NULL;
	}

	void RendererOpenGL::CoreInitialize()
	{
		glewInit();
		
		glClearDepth(1.f);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);
		hdrShader.LoadShaders("Shaders/hdr.vs", "Shaders/hdr.fs", nullptr);
		hdrShader.Create();
		hdrShader.Bind();
		glUniform1i(glGetUniformLocation(hdrShader.Get(), "screenTex"), 0);

		CreateRenderQuad();
	}

	void RendererOpenGL::CorePreparePostProcess()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererOpenGL::CorePostProcess()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		hdrShader.Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texFBO);
		RenderQuad();
		hdrShader.Unbind();
	}

	void RendererOpenGL::CoreUnbind()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void RendererOpenGL::CoreBindAttrib()
	{
		_program.Bind();

		uint32_t matrixBlockIndex = glGetUniformBlockIndex(_program.Get(), "MatrixBlock");
		glUniformBlockBinding(_program.Get(), matrixBlockIndex, 0);

		uint32_t colorsBlockIndex = glGetUniformBlockIndex(_program.Get(), "ColorBlock");
		glUniformBlockBinding(_program.Get(), colorsBlockIndex, 1);

		uint32_t programID = _program.Get();
		int positionLocation = glGetAttribLocation(programID, "a_Position");
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, false, 8 * sizeof(float), 0);
		glEnableVertexAttribArray(positionLocation);

		int texcoordsLocation = glGetAttribLocation(programID, "a_TexCoords");
		glVertexAttribPointer(texcoordsLocation, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(texcoordsLocation);

		int normalLocation = glGetAttribLocation(programID, "a_Normal");
		glVertexAttribPointer(normalLocation, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(normalLocation);
	}

	void RendererOpenGL::CoreRegisterSkybox()
	{
	}

	void RendererOpenGL::LoadTexture(resource::LoadMode loadMode, std::string path, resource::Mesh* mesh)
	{
		switch (loadMode)
		{
		case resource::DDS:
			DDSLoad(path, mesh);
			break;
		case resource::STBI:
			STBILoad(path, mesh);
			break;
		default:
			break;
		}
	}

	void RendererOpenGL::STBILoad(std::string path, resource::Mesh* mesh)
	{
		int w, h, c;
		uint8_t* imageData = stbi_load(path.c_str(), &w, &h, &c, STBI_rgb_alpha);
		glGenTextures(1, &mesh->GetMaterial()->GetTexture()->TextureData._texture);
		glBindTexture(GL_TEXTURE_2D, mesh->GetMaterial()->GetTexture()->TextureData._texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		stbi_image_free(imageData);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void RendererOpenGL::DDSLoad(std::string path, resource::Mesh* mesh)
	{
		//TODO : IMPLEMENT DDS WITH A LIB

		/*uint16_t mipmapMinimum = CountMipMapDDS(path.c_str());

		uint32_t wDDS, hDSS;
		uint8_t* output;*/

		//glGenTextures(1, &mesh->GetTexture()->TextureData._texFBO);
		//glBindTexture(GL_TEXTURE_2D, mesh->GetTexture()->TextureData._texFBO);
	}

	uint32_t RendererOpenGL::LoadCubeMap(std::vector<const char*> faces, uint32_t texSkybox)
	{
		return NULL;
	}

	void RendererOpenGL::UpdateDeltaTime()
	{
		float currentFrame = glutGet(GLUT_ELAPSED_TIME);
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;
	}

	void RendererOpenGL::InitializeSkybox(uint32_t texSkybox)
	{
	}

	void RendererOpenGL::RenderQuad()
	{
		glBindVertexArray(_quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	void RendererOpenGL::RenderGrid(int numberOfLines)
	{
	}

	void RendererOpenGL::CreateRenderQuad()
	{
		GLuint quadVBO;

		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// Setup plane VAO
		glGenVertexArrays(1, &_quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(_quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}

	void RendererOpenGL::CoreSendMatrixToShader(Maths::Mat4 matrix, const char* uniformVariableName)
	{
		uint32_t w = glGetUniformLocation(_program.Get(), uniformVariableName);
		glUniformMatrix4fv(w, 1, false, matrix.m);
	}
}