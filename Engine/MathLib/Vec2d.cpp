#include "Vec2d.h"

#include <cmath>

#include "Tools.h"

namespace Maths
{
	Vec2d::Vec2d()
		: x(0.0), y(0.0)
	{
	}

	Vec2d::Vec2d(float _x, float _y)
		: x(_x), y(_y)
	{
	}

	Vec2d::~Vec2d()
	{
	}

	float Vec2d::Norm()
	{
		return sqrt(x * x + y * y);
	}

	Vec2d Vec2d::Normalize()
	{
		float norm = Norm();
		if (norm != 0)
		{
			x = x / norm;
			y = y / norm;
		}

		return Vec2d();
	}

	float Vec2d::DotProduct(const Vec2d& vec) const
	{
		return (x * vec.x) + (y * vec.y);
	}

	const float Vec2d::DotProduct(const Vec2d& vec1, const Vec2d & vec2)
	{
		return (vec1.x * vec2.x) + (vec1.y * vec2.y);
	}

	bool operator==(const Vec2d & vec1, const Vec2d & vec2)
	{
		if (Tools::CompareFloat(vec1.x, vec2.x) && Tools::CompareFloat(vec1.y, vec2.y))
			return true;

		return false;
	}

	bool operator!=(const Vec2d & vec1, const Vec2d & vec2)
	{
		return !(vec1 == vec2);
	}

	Vec2d operator*(const Vec2d & vec, const float scalar)
	{
		return Vec2d(scalar * vec.x, scalar * vec.y);
	}

	Vec2d operator*(const float scalar, const Vec2d & vec)
	{
		return Vec2d(scalar * vec.x, scalar * vec.y);
	}

	Vec2d operator+(const Vec2d & vec1, const Vec2d & vec2)
	{
		return Vec2d(vec1.x + vec2.x, vec1.y + vec2.y);
	}

	Vec2d operator-(const Vec2d & vec1, const Vec2d & vec2)
	{
		return Vec2d(vec1.x - vec2.x, vec1.y - vec2.y);
	}

	Vec2d operator+=(Vec2d & vec1, const Vec2d & vec2)
	{
		vec1.x += vec2.x;
		vec1.y += vec2.y;

		return vec1;
	}

	Vec2d operator-=(Vec2d & vec1, const Vec2d & vec2)
	{
		vec1.x -= vec2.x;
		vec1.y -= vec2.y;

		return vec1;
	}
}