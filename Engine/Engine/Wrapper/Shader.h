#pragma once
#include "../../Common/GLShader.h"

namespace resource
{
	class Shader
	{
	public:
		Shader();
		Shader(const char* shaderVS, const char* shaderFS);
		~Shader();

		void InitializeShader();

		static const uint32_t GetProgramID() { return _programID; };

	private:
		GLShader _basicProgram;
		static uint32_t _programID;
		const char *_vertexShader = nullptr;
		const char *_fragmentShader = nullptr;


	};
}