#include "Shader.h"
#include "../LogDebug/ILogger.h"

uint32_t resource::Shader::_programID = 0;

namespace resource
{
	Shader::Shader()
	{
		core::ILogger::LogMessage("Create Shader at : ", __FILE__, __LINE__);
	}

	Shader::Shader(const char* shaderVS, const char* shaderFS)
	:_vertexShader(shaderVS), _fragmentShader(shaderFS)
	{
		core::ILogger::LogMessage("Create Shader at : ", __FILE__, __LINE__);
	}

	Shader::~Shader()
	{
		core::ILogger::LogMessage("Delete Shader at : ", __FILE__, __LINE__);
		_basicProgram.Destroy();
		delete[] _vertexShader;
		delete[] _fragmentShader;
	}

	void Shader::InitializeShader()
	{
		_basicProgram.LoadShaders(_vertexShader, _fragmentShader);
		_basicProgram.Create();
		_basicProgram.Bind();
		_programID = _basicProgram.Get();
	}
}