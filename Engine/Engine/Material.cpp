#include "Material.h"
#include "LogDebug\ILogger.h"
#include "Texture.h"

namespace resource
{
	Material::Material()
	{
		core::ILogger::LogMessage("Create Material at : ", __FILE__, __LINE__);
		if (_texture == nullptr)
		{
			_texture = new Texture();
		}
	}

	Material::Material(Material* mat)
	{
		_name = mat->_name;
		_ambiantColor = mat->_ambiantColor;
		_specularColor = mat->_specularColor;
		_diffuseColor = mat->_diffuseColor;
		_ambiantColor = mat->_ambiantColor;
	}

	Material::~Material()
	{
		core::ILogger::LogMessage("Delete Material at : ", __FILE__, __LINE__);
		delete _texture;
		_texture = nullptr;
		delete[] _vertexShader;
		delete[] _fragmentShader;
		delete[] _geometryShader;
		_name.erase();
	}

	void Material::SetName(std::string& name)
	{
		_name = name;
	}

	const std::string Material::GetName() const
	{
		return _name;
	}


	void Material::AddSpecularColor(const float r, const float g, const float b)
	{
		_specularColor.x = r;
		_specularColor.y = g;
		_specularColor.z = b;
	}

	void Material::AddAmbiantColor(const float r, const float g, const float b)
	{
		_ambiantColor.x = r;
		_ambiantColor.y = g;
		_ambiantColor.z = b;
	}

	void Material::AddDiffuseColor(const float r, const float g, const float b)
	{
		_diffuseColor.x = r;
		_diffuseColor.y = g;
		_diffuseColor.z = b;
	}

	void Material::AddMaterial(const float r, const float g, const float b, EMaterialType materialType)
	{
		switch (materialType)
		{
		case Diffuse:
			AddDiffuseColor(r, g, b);
			break;
		case Specular:
			AddSpecularColor(r, g, b);
			break;
		case Ambiant:
			AddAmbiantColor(r, g, b);
			break;
		default:
			break;
		}
	}

	void Material::SetFragmentShader(const char* fragmentShader)
	{
		_fragmentShader = fragmentShader;
	}

	void Material::SetVertexShader(const char* vertexShader)
	{
		_vertexShader = vertexShader;
	}

	void Material::SetGeometryShader(const char* geometryShader)
	{
		_geometryShader = geometryShader;
	}

	const char* Material::GetVertexShader() const
	{
		return _vertexShader;
	}

	const char* Material::GetFragmentShader() const
	{
		return _fragmentShader;
	}

	const char* Material::GetGeometryShader() const
	{
		return _geometryShader;
	}

	void Material::AddTexture(std::string texture)
	{
		_texture->TextureData._path = texture;
	}

	Texture* Material::GetTexture() const
	{
		return _texture;
	}

}