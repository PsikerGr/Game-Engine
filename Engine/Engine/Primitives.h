#pragma once
#include "../MathLib/Vec3d.h"
#include "Wrapper/Shader.h"
#include "Mesh.h"

namespace primitives
{
	class Triangle
	{
	public:
		Triangle();
		~Triangle();

		void CreateTriangle();
		void CreateTriangle(Maths::Vec3d point1, Maths::Vec3d point2, Maths::Vec3d point3);

	private:
		resource::Shader* _shader;
		resource::Mesh* _triangle;
	};

	class Square
	{
	public:
		Square();
		~Square();
		// Create a Square with default values
		void CreateSquare();
		void CreateSquare(Maths::Vec3d point1, Maths::Vec3d point2, Maths::Vec3d point3, Maths::Vec3d point4);
		void CreateSquare(float point1X, float point1Y, float point1Z, float point2X, float point2Y, float point2Z, float point3X, float point3Y, float point3Z, float point4X, float point4Y, float point4Z);
		void DrawSquare();

	private:
		resource::Shader* _shader;
		resource::Mesh* _square;
	};
}