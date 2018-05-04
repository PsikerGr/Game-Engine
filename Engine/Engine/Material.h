#pragma once
#include <vector>
#include "../MathLib/Vec3d.h"


namespace resource
{
	class Texture;

	enum EMaterialType
	{
		Diffuse = 0,
		Specular,
		Ambiant
	};

	class Material
	{
	public:
		Material();
		Material(Material* mat);
		~Material();

		void SetName(std::string& name);
		const std::string GetName() const;

		void AddSpecularColor(const float r, const float g, const float b);
		void AddAmbiantColor(const float r, const float g, const float b);
		void AddDiffuseColor(const float r, const float g, const float b);

		void AddMaterial(const float r, const float g, const float b, EMaterialType materialType);

		void SetVertexShader(const char* vertexShader);
		const char* GetVertexShader() const;

		void SetFragmentShader(const char* fragmentShader);
		const char* GetFragmentShader() const;

		void SetGeometryShader(const char* geometryShader);
		const char* GetGeometryShader() const;

		void AddTexture(std::string texture);

		Texture* GetTexture() const;

		Maths::Vec3d _specularColor = { 1, 1, 1 };
		float _specularOffset = 0;

		Maths::Vec3d _ambiantColor = { 1, 1, 1 };
		float _ambiantOffset = 0;

		Maths::Vec3d _diffuseColor = { 1, 1, 1 };
		float _diffuseOffset = 0;


	private:
		std::string _name;
		const char* _vertexShader, *_fragmentShader, *_geometryShader;
		Texture* _texture;

		

	};



}
