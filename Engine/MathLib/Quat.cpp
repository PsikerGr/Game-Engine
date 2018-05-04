#include "Quat.h"
#include "Mat4.h"

#include <iostream>
#include <string>

#include "Tools.h"

namespace Maths
{
	Quat::Quat()
		: w(0.0f), x(0.0f), y(0.0f), z(0.0f)
	{

	}

	Quat::Quat(const float _w, const float _x, const float _y, const float _z)
		: w(_w), x(_x), y(_y), z(_z)
	{

	}

	Quat::~Quat()
	{

	}

	float Quat::Norm() const
	{
		return sqrtf(w * w + x * x + y * y + z * z);
	}

	Quat Quat::Normalize()
	{
		float norm = Norm();
		if (norm != 0)
		{
			w = w / norm;
			x = x / norm;
			y = y / norm;
			z = z / norm;
		}

			return Quat();
	}

	float Quat::ScalarProduct(const Quat& q1, const Quat& q2)
	{
		return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	}

	Quat Quat::Lerp(Quat& q1, Quat& q2, const float t)
	{
		return Quat(q1 + t * (q2 - q1));
	}

	Quat Quat::Slerp(Quat& q1, Quat& q2, const float t)
	{
		q1.Normalize();
		q2.Normalize();

		float dot = Quat::ScalarProduct(q1, q2);

		const float DOT_THRESHOLD = 0.9995f;
		if (dot > DOT_THRESHOLD)
		{
			Quat result = q1 + t * (q2 - q1);
			result.Normalize();
			return result;
		}

		if (dot < 0.0f)
		{
			q2 = -q2;
			dot = -dot;
		}

		float theta0 = acosf(dot);
		float theta = theta0 * t;

		Quat newQuat = q2 - q1 * dot;
		newQuat.Normalize();

		return q1 * cos(theta) + newQuat * sin(theta);
	}

	Quat Quat::Nlerp(Quat& q1, Quat& q2, const float t)
	{
		Quat newQuat = Quat::Lerp(q1, q2, t);
		newQuat.Normalize();

		return newQuat;
	}

	Quat Quat::AngleToQuat(Vec3d angle)
	{
		float t0 = cos(Tools::DegToRad(angle.z) / 2);
		float t1 = sin(Tools::DegToRad(angle.z) / 2);
		float t2 = cos(Tools::DegToRad(angle.x) / 2);
		float t3 = sin(Tools::DegToRad(angle.x) / 2);
		float t4 = cos(Tools::DegToRad(angle.y) / 2);
		float t5 = sin(Tools::DegToRad(angle.y) / 2);
		
		Quat result;
		
		result.w = t0 * t2 * t4 + t1 * t3 * t5;
		result.x = t0 * t3 * t4 - t1 * t2 * t5;
		result.y = t0 * t2 * t5 + t1 * t3 * t4;
		result.z = t1 * t2 * t4 - t0 * t3 * t5;

		return result;
	}

	Quat Quat::MatrixToQuat(Mat4 mat)
	{		
		Quat quat;

		float t;

		if (mat.m[8] < 0)
		{
			if (mat.m[0] > mat.m[1])
			{
				t = 1 + mat.m[0] - mat.m[4] - mat.m[8];
				quat.x = t;
				quat.y = mat.m[1] + mat.m[3];
				quat.z = mat.m[6] + mat.m[2];
				quat.w = mat.m[5] - mat.m[7];
			}
			else
			{
				t = 1 - mat.m[0] + mat.m[4] - mat.m[8];
				quat.x = mat.m[1] + mat.m[3];
				quat.y = t;
				quat.z = mat.m[5] + mat.m[7];
				quat.w = mat.m[6] - mat.m[2];
			}
		}
		else
		{
			if (mat.m[0] < -mat.m[4])
			{
				t = 1 - mat.m[0] - mat.m[4] + mat.m[8];
				quat.x = mat.m[6] + mat.m[2];
				quat.y = mat.m[5] + mat.m[7];
				quat.z = t;
				quat.w = mat.m[1] - mat.m[3];
			}
			else
			{
				t = 1 + mat.m[0] + mat.m[4] + mat.m[8];
				quat.x = mat.m[5] - mat.m[7];
				quat.y = mat.m[6] - mat.m[2];
				quat.z = mat.m[1] - mat.m[3];
				quat.w = t;
			}
		}

		quat *= 0.5f / sqrt(t);

		return quat;
	}

	bool operator==(const Quat & quat1, const Quat & quat2)
	{
		if (Tools::CompareFloat(quat1.x, quat2.x) && Tools::CompareFloat(quat1.y, quat2.y) && Tools::CompareFloat(quat1.z, quat2.z) && Tools::CompareFloat(quat1.w, quat2.w))
			return true;

		return false;
	}

	bool operator!=(const Quat & quat1, const Quat & quat2)
	{
		return !(quat1 == quat2);
	}

	Quat operator*(const float& factor, const Quat& quat)
	{
		return Quat(quat.w * factor, quat.x * factor, quat.y * factor, quat.z * factor);
	}

	Quat operator*(const Quat& quat, const float& factor)
	{
		return Quat(quat.w * factor, quat.x * factor, quat.y * factor, quat.z * factor);
	}

	Quat operator+(const Quat& quat1, const Quat& quat2)
	{
		return Quat(quat1.w + quat2.w, quat1.x + quat2.x, quat1.y + quat2.y, quat1.z + quat2.z);
	}

	Quat operator-(const Quat& quat)
	{
		return Quat(-quat.w, -quat.x, -quat.y, -quat.z);
	}

	Quat operator-(const Quat& quat1, const Quat& quat2)
	{
		return Quat(quat1.w - quat2.w, quat1.x - quat2.x, quat1.y - quat2.y, quat1.z - quat2.z);
	}

	Quat operator+=(Quat& quat1, const Quat& quat2)
	{
		quat1.w += quat2.w;
		quat1.x += quat2.x;
		quat1.y += quat2.y;
		quat1.z += quat2.z;

		return quat1;
	}

	Quat operator-=(Quat & quat1, const Quat & quat2)
	{
		quat1.x -= quat2.x;
		quat1.y -= quat2.y;
		quat1.z -= quat2.z;
		quat1.w -= quat2.w;

		return quat1;
	}
	Quat operator*(const Quat & quat1, const Quat & quat2)
	{
		Quat t;
		
		t.x = quat1.x * quat2.w + quat1.y * quat2.z - quat1.z * quat2.y + quat1.w * quat2.x;
		t.y = -quat1.x * quat2.z + quat1.y * quat2.w + quat1.z * quat2.x + quat1.w * quat2.y;
		t.z = quat1.x * quat2.y - quat1.y * quat2.x + quat1.z * quat2.w + quat1.w * quat2.z;
		t.w =- quat1.x * quat2.x - quat1.y * quat2.y - quat1.z * quat2.z + quat1.w * quat2.w;

		return t;
	}
	
	Quat& operator*=(Quat& quat, const float scalar)
	{
		quat.x *= scalar;
		quat.y *= scalar;
		quat.z *= scalar;
		quat.w *= scalar;

		return quat;
	}
}