#include "Primitives.h"
#include "Device.h"
#include "LogDebug\ILogger.h"

namespace primitives
{
	Triangle::Triangle()
	{
		core::ILogger::LogMessage("Create Triangle at : ", __FILE__, __LINE__);
	}

	Triangle::~Triangle()
	{
		core::ILogger::LogMessage("Delete Triangle at : ", __FILE__, __LINE__);
		delete _shader;
		delete _triangle;
	}

	void Triangle::CreateTriangle()
	{
		std::vector<float> triangleVertices = { -0.5f, -0.5f, 0.5,
			0.5f, -0.5f, 0.5,
			0.5, 0.5f, 0.5 };

		std::vector<uint16_t> triangleIndices = { 0, 1, 2 };
	}

	void Triangle::CreateTriangle(Maths::Vec3d point1, Maths::Vec3d point2, Maths::Vec3d point3)
	{
		std::vector<float> triangleVertices = { point1.x, point1.y, point1.z, point2.x, point2.y, point2.z, point3.x, point3.y, point3.z };

		std::vector<uint16_t> triangleIndices = { 0, 1, 2 };
	}

	Square::Square()
	{
		core::ILogger::LogMessage("Create Square at : ", __FILE__, __LINE__);
	}

	Square::~Square()
	{
		core::ILogger::LogMessage("Delete Square at : ", __FILE__, __LINE__);
		delete _shader;
		delete _square;
	}

	void Square::CreateSquare()
	{
		std::vector<float> squareVertices = { -0.5f, -0.5f, 0.5f,
			0.5f, -0.5f,  0.5f,
			-0.5f, 0.5f, 0.5f,
			0.5f, 0.5f , 0.5f };

		std::vector<uint16_t> squareIndices = { 0, 1, 2, 1, 3, 2 };
	}

	void Square::CreateSquare(Maths::Vec3d point1, Maths::Vec3d point2, Maths::Vec3d point3, Maths::Vec3d point4)
	{
		std::vector<float> squareVertices = { point1.x , point1.y , point1.z,
			point2.x, point2.y, point2.z,
			point3.x, point3.y, point3.z,
			point4.x, point4.y , point4.z };

		std::vector<uint16_t> squareIndices = { 0, 1, 2, 1, 3, 2 };
	}

	void Square::CreateSquare(float point1X, float point1Y, float point1Z, float point2X, float point2Y, float point2Z, float point3X, float point3Y, float point3Z, float point4X, float point4Y, float point4Z)
	{
		std::vector<float> squareVertices = { point1X, point1Y, point1Z,
			point2X, point2Y, point2Z,
			point3X, point3Y, point3Z,
			point4X, point4Y, point4Z };

		std::vector<uint16_t> squareIndices = { 0, 1, 2, 1, 3, 2 };
	}

	void Square::DrawSquare()
	{
	}
}