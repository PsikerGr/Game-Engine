#pragma once
namespace Maths
{
	struct Vec2d
	{
		Vec2d();
		Vec2d(float _x, float _y);
		~Vec2d();

		float x;
		float y;

		float Norm();
		Vec2d Normalize();
		float DotProduct(const Vec2d& vec) const;
		static const float DotProduct(const Vec2d& vec1, const Vec2d& vec2);
	};

	bool operator ==(const Vec2d& vec1, const Vec2d& vec2);
	bool operator !=(const Vec2d& vec1, const Vec2d& vec2);
	Vec2d operator*(const Vec2d& vec, const float scalar);
	Vec2d operator*(const float scalar, const Vec2d& vec);
	Vec2d operator +(const Vec2d& vec1, const Vec2d& vec2);
	Vec2d operator -(const Vec2d& vec1, const Vec2d& vec2);
	Vec2d operator +=(Vec2d& vec1, const Vec2d& vec2);
	Vec2d operator -=(Vec2d& vec1, const Vec2d& vec2);
}