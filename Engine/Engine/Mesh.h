#pragma once


#include <iostream>
#include <vector>


#include "Wrapper/Shader.h"
#include "Transform.h"

#include "Texture.h"
#include "../Common/GLShader.h"
#include "Component.h"


namespace resource
{
	class Material;

	class Mesh : public Component
	{
	public:
		Mesh();
		~Mesh();
	
		
		struct RenderData
		{
			uint32_t _VAO;
			uint32_t _VBO;
			uint32_t _IBO;
		} RenderData;

		void SetVertices(const float* vertices, const uint32_t vertexSize);
		inline const float* GetVertices() const { return _vertices; }
		
		void SetIndices(uint32_t* indices, const uint32_t indicesSize);
		inline const uint32_t* GetIndices() const { return _indices; }
		
		void SetIndicesCount(uint32_t count);
		const uint32_t GetIndicesCount() const;

		void SetName(std::string name);
		const std::string GetName();

		Material* GetMaterial() const;
		void SetMaterial(Material* material);


	private:
		float* _vertices, *_normals, *_colours;
		uint32_t* _indices;
		uint32_t _indicesCount;
		uint32_t _bufferTexture;

		Material* _material;

		std::string _name;
	
	};
}