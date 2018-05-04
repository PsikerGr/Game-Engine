#include "Vec3d.h"

#include <cmath>

#include "Tools.h"

namespace Maths
{
	Vec3d::Vec3d()
		:x(0.0), y(0.0), z(0.0)
	{
	}

	Vec3d::Vec3d(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{
	}

	Vec3d::~Vec3d()
	{
	}

	float Vec3d::Norm()
	{
		return sqrt(x * x + y * y + z * z);
	}

	void Vec3d::Normalize()
	{
		float norm = Norm();
		if (norm != 0)
		{
			x = x / norm;
			y = y / norm;
			z = z / norm;
		}
	}

	Vec3d Vec3d::Normalized()
	{
		float norm = Norm();
		Vec3d vec;
		if (norm != 0)
		{
			vec.x = x / norm;
			vec.y = y / norm;
			vec.z = z / norm;
		}
		
		return vec;
	}

	float Vec3d::DotProduct(const Vec3d & vec) const
	{
		return (x * vec.x) + (y * vec.y) + (z * vec.z);
	}

	const float Vec3d::DotProduct(const Vec3d & vec1, const Vec3d & vec2)
	{
		return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
	}

	Vec3d Vec3d::CrossProduct(const Vec3d & vec) const
	{
		Vec3d vector;
		vector.x = (y*vec.z) - (z * vec.y);
		vector.y = (z * vec.x) - (x * vec.z);
		vector.z = (x * vec.y) - (y * vec.x);

		return vector;
	}

	const Vec3d Vec3d::CrossProduct(const Vec3d & vec1, const Vec3d & vec2)
	{
		Vec3d vector;
		vector.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
		vector.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
		vector.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);

		return vector;
	}

	bool operator==(const Vec3d & vec1, const Vec3d & vec2)
	{		
		if (Tools::CompareFloat(vec1.x, vec2.x) && Tools::CompareFloat(vec1.y, vec2.y) && Tools::CompareFloat(vec1.z, vec2.z))
			return true;

		return false;
	}

	bool operator!=(const Vec3d & vec1, const Vec3d & vec2)
	{
		return !(vec1 == vec2);
	}

	Vec3d operator*(const Vec3d & vec, const float scalar)
	{
		return Vec3d(scalar * vec.x, scalar * vec.y, scalar * vec.z);
	}

	Vec3d operator*(const float scalar, const Vec3d & vec)
	{
		return Vec3d(scalar * vec.x, scalar * vec.y, scalar * vec.z);
	}

	Vec3d operator+(const Vec3d & vec1, const Vec3d & vec2)
	{
		return Vec3d(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
	}

	Vec3d operator-(const Vec3d & vec1, const Vec3d & vec2)
	{
		return Vec3d(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
	}

	Vec3d operator-(const Vec3d& vec)
	{
		return Vec3d(-vec.x, -vec.y, -vec.z);
	}

	Vec3d operator+=(Vec3d & vec1, const Vec3d & vec2)
	{
		vec1.x += vec2.x;
		vec1.y += vec2.y;
		vec1.z += vec2.z;

		return vec1;
	}

	Vec3d operator-=(Vec3d & vec1, const Vec3d & vec2)
	{
		vec1.x -= vec2.x;
		vec1.y -= vec2.y;
		vec1.z -= vec2.z;

		return vec1;
	}
}