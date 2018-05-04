#include <cmath>
#include "Vec3.h"

namespace Maths
{

	Vec3::Vec3()
		:x(0.0), y(0.0), z(0.0)
	{
	}

	Vec3::Vec3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{
	}

	Vec3::~Vec3()
	{
	}

	float Vec3::Norm()
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vec3 Vec3::Normalize()
	{
		Vec3 vector;
		float norm = this->Norm();
		if (norm != 0)
		{
			vector.x = x / norm;
			vector.y = y / norm;
			vector.z = z / norm;
		}

		return vector;
	}

	float Vec3::DotProduct(const Vec3 & vec) const
	{
		return (x * vec.x) + (y * vec.y) + (z * vec.z);
	}

	Vec3 Vec3::CrossProduct(const Vec3 & vec) const
	{
		Vec3 vector;

		vector.x = (y*vec.z) - (z * vec.y);
		vector.y = (z * vec.x) - (x - vec.z);
		vector.z = (x * vec.y) - (y * vec.x);

		return vector;
	}

	bool operator==(const Vec3 & vec1, const Vec3 & vec2)
	{
		return (vec1 == vec2);
	}

	bool operator!=(const Vec3 & vec1, const Vec3 & vec2)
	{
		return !(vec1 == vec2);
	}

	Vec3 operator+(Vec3 & vec1, const Vec3 & vec2)
	{
		vec1 += vec2;
		return vec1;
	}

	Vec3 operator-(Vec3 & vec1, const Vec3 & vec2)
	{
		vec1 -= vec2;
		return vec1;
	}

	Vec3 operator+=(Vec3 & vec1, const Vec3 & vec2)
	{
		vec1.x += vec2.x;
		vec1.y += vec2.y;
		vec1.z += vec2.z;

		return vec1;
	}

	Vec3 operator-=(Vec3 & vec1, const Vec3 & vec2)
	{
		vec1.x -= vec2.x;
		vec1.y -= vec2.y;
		vec1.z -= vec2.z;
		return vec1;
	}

	Vec3& Vec3::operator*=(const float f)
	{
		x *= f; y *= f; z *= f;

		return *this;
	}

	Vec3 operator*(Vec3 vec, float f)
	{
		vec.x *= f; vec.y *= f, vec.z *= f;
		return vec;
	}

	void Vec3::operator=(const Vec3 &vec)
	{
		x = vec.x; y = vec.y; z = vec.z;
	}
	

}