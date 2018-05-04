#include "Mesh.h"

#include <cassert>

#include "Wrapper/Shader.h"
#include "LogDebug\ILogger.h"
#include "Material.h"

namespace resource
{
	Mesh::Mesh()
	: Component("Mesh Renderer")
	{
		core::ILogger::LogMessage("Create Mesh at : ", __FILE__, __LINE__);

		if (_material == nullptr)
		{
			_material = new Material();
		}
	}

	Mesh::~Mesh()
	{
		core::ILogger::LogMessage("Delete Mesh at : ", __FILE__, __LINE__);

		{
			delete[] _vertices;
			delete[] _normals;
			delete[] _indices;
			delete _material;
			delete _material;
			_material = nullptr;
			_name.erase();

		}

	}

	const uint32_t Mesh::GetIndicesCount() const
	{
		return _indicesCount;
	}

	void Mesh::SetVertices(const float* vertices, const uint32_t vertexSize)
	{
		_vertices = new float[vertexSize];

		memcpy(_vertices, vertices, vertexSize * sizeof(float));

	}

	void Mesh::SetIndices(uint32_t* indices, const uint32_t indicesSize)
	{
		_indices = new uint32_t[indicesSize];
		memcpy(_indices, indices, indicesSize * sizeof(uint32_t));

	}

	void Mesh::SetIndicesCount(uint32_t count)
	{
		_indicesCount = count;
	}


	void Mesh::SetName(std::string name)
	{
		_name = name;
	}

	const std::string Mesh::GetName()
	{
		return _name;
	}
	
	Material* Mesh::GetMaterial() const
	{
		return _material;
	}

	void Mesh::SetMaterial(Material* material)
	{
		_material = material;
	}

}