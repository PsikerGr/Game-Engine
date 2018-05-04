#pragma once

namespace Maths
{
	struct Vec3d
	{
		Vec3d();
		Vec3d(float _x, float _y, float _z);
		~Vec3d();

		float x;
		float y;
		float z;

		float Norm();
		void Normalize();
		Vec3d Normalized();
		float DotProduct(const Vec3d& vec) const;
		static const float DotProduct(const Vec3d& vec1, const Vec3d& vec2);
		Vec3d CrossProduct(const Vec3d& vec) const;
		static const Vec3d CrossProduct(const Vec3d& vec1, const Vec3d& vec2);
	};

	bool operator==(const Vec3d& vec1, const Vec3d& vec2);
	bool operator!=(const Vec3d& vec1, const Vec3d& vec2);
	Vec3d operator*(const Vec3d& vec, const float scalar);
	Vec3d operator*(const float scalar, const Vec3d& vec);
	Vec3d operator+(const Vec3d& vec1, const Vec3d& vec2);
	Vec3d operator-(const Vec3d& vec1, const Vec3d& vec2);
	Vec3d operator-(const Vec3d& vec);
	Vec3d operator+=(Vec3d& vec1, const Vec3d& vec2);
	Vec3d operator-=(Vec3d& vec1, const Vec3d& vec2);
}