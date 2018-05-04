#pragma once

#include "Vec3d.h"


namespace Maths
{
	struct Mat4;

	struct Quat
	{
		Quat();
		Quat(const float _w, const float _x, const float _y, const float _z);
		~Quat();

		float	w;
		float	x;
		float	y;
		float	z;

		float Norm() const;
		Quat Normalize();
		static float ScalarProduct(const Quat& q1, const Quat& q2);
		static Quat Lerp(Quat& q1, Quat& q2, const float t);
		static Quat Slerp(Quat& q1, Quat& q2, const float t);
		static Quat Nlerp(Quat& q1, Quat& q2, const float t);
		static Quat AngleToQuat(Vec3d angle);
		static Quat MatrixToQuat(Mat4 mat);
	};

	bool operator==(const Quat& quat1, const Quat& quat2);
	bool operator!=(const Quat& quat1, const Quat& quat2);
	Quat operator*(const float& factor, const Quat& quat);
	Quat operator*(const Quat& quat, const float& factor);
	Quat operator+(const Quat& quat1, const Quat& quat2);
	Quat operator-(const Quat& quat);
	Quat operator-(const Quat& quat1, const Quat& quat2);
	Quat operator+=(Quat& quat1, const Quat& quat2);
	Quat operator-=(Quat& quat1, const Quat& quat2);
	Quat operator*(const Quat& quat1, const Quat& quat2);
	Quat& operator*=(Quat& quat, const float scalar);
};