#include "GL/glew.h"
#include "GLShader.h"

#include <fstream>
#include <iostream>



bool GLShader::LoadShader(uint32_t type, const char* path)
{
	uint32_t shaderID;
	shaderID = glCreateShader(type);

	switch (type)
	{
	case GL_VERTEX_SHADER:
		_VertexShader = shaderID;
		break;

	case GL_FRAGMENT_SHADER:
		_FragmentShader = shaderID;
		break;

	case GL_GEOMETRY_SHADER:
		_GeometryShader = shaderID;
		break;

	default:
		break;
	}

	std::ifstream fileStream;
	fileStream.open(path, std::ios::binary);
	if (!fileStream.is_open())
	{
		std::cout << "Cannot open " << path << std::endl;
		return false;
	}
	std::streampos begin = fileStream.tellg();
	fileStream.seekg(0, std::ios::end);
	uint32_t file_len = fileStream.tellg();
	char* buffer = new char[file_len + 1];
	fileStream.seekg(0, std::ios::beg);
	fileStream.read(buffer, file_len);
	fileStream.close();

	buffer[file_len] = '\0';
	glShaderSource(shaderID, 1, &buffer, nullptr);
	
	delete[] buffer;
	glCompileShader(shaderID);

	int compileSuccess = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileSuccess);
	if (!compileSuccess)
	{
		char errorBuffer[4096];
		int error_len;
		glGetShaderInfoLog(shaderID, 4096, &error_len, errorBuffer);
		std::cout << "erreur dans le " << (type == GL_VERTEX_SHADER ? " vertex" : " fragment") << " shader : " << errorBuffer << std::endl;
		return false;
	}

	return true;
}

void GLShader::LoadShaders(const char * vertexShader, const char * fragmentShader, const char * geometryShader)
{
	// Implementer le log error et mettre des garde sur chaque fonction necessitant un check


	if (vertexShader != nullptr && fragmentShader != nullptr)
	{
		LoadShader(GL_VERTEX_SHADER, vertexShader);
		LoadShader(GL_FRAGMENT_SHADER, fragmentShader);
	}
		
	if (geometryShader != nullptr)
	{
		LoadShader(GL_GEOMETRY_SHADER, geometryShader);
	}
}

bool GLShader::Create()
{
	_Program = glCreateProgram();

	glAttachShader(_Program, _VertexShader);
	if (_GeometryShader != NULL)
	{
		glAttachShader(_Program, _GeometryShader);
	}
	glAttachShader(_Program, _FragmentShader);
	
	if (LinkCallBack != nullptr)
		LinkCallBack(_Program);

	//glBindAttribLocation(_Program, 0, "a_Position");
	////glBindAttribLocation(_Program, 1, "a_Color");
	//glBindAttribLocation(_Program, 2, "a_TexCoords");
	//glBindAttribLocation(_Program, 1, "a_Normal");

	glLinkProgram(_Program);

	int linkSuccess = 0;
	glGetProgramiv(_Program, GL_LINK_STATUS, &linkSuccess);
	if (!linkSuccess)
	{
		char errorBuffer[4096];
		int error_len;
		glGetProgramInfoLog(_Program, 4096, &error_len, errorBuffer);
		std::cout << "erreur de linkage :  " << errorBuffer << std::endl;
		return false;
	}

	return true;
}

void GLShader::Bind()
{
	glUseProgram(_Program);

}

void GLShader::Destroy()
{
	glDeleteShader(_VertexShader);
	glDeleteShader(_FragmentShader);
	if (_GeometryShader != NULL)
	{
		glDeleteShader(_GeometryShader);
	}
	glDeleteProgram(_Program);
}

void GLShader::Unbind()
{
	glUseProgram(0);
}
