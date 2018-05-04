
#include <cmath>
#include <iomanip>
#include <iostream>

#include "Mat4.h"
#include "Quat.h"
#include "Vec3d.h"
#include "Tools.h"

namespace Maths
{
	Mat4::Mat4()
	{
		for (size_t i = 0; i < 16; i++)
		{
			m[i] = 0.0f;
		}
	}

	Mat4::Mat4(float _m[16])
	{
		for (size_t i = 0; i < 16; ++i)
		{
			m[i] = _m[i];
		}
	}

	Mat4::Mat4(float m0, float m1, float m2, float m3, float m4, float m5,
		float m6, float m7, float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15)
	{
		m[0] = m0;	m[4] = m4;	m[8] = m8;		m[12] = m12;
		m[1] = m1;	m[5] = m5;	m[9] = m9;		m[13] = m13;
		m[2] = m2;	m[6] = m6;	m[10] = m10;	m[14] = m14;
		m[3] = m3;	m[7] = m7;	m[11] = m11;	m[15] = m15;
	}

	Mat4::Mat4(const Vec3d right, const Vec3d up, const Vec3d forward, const Vec3d position)
	{
		Identity();

		m[0] = right.x;	m[4] = up.x;	m[8] = forward.x;	m[12] = position.x;
		m[1] = right.y;	m[5] = up.y;	m[9] = forward.y;	m[13] = position.y;
		m[2] = right.z;	m[6] = up.z;	m[10] = forward.z;	m[14] = position.z;
	}

	Mat4 Mat4::Identity()
	{
		for (int i = 0; i <= 15; i++)
		{
			if (i == 0 || i == 5 || i == 10 || i == 15)
				m[i] = 1.0f;
			else
				m[i] = 0.0f;
		}

		return Mat4(m);
	}

	Mat4& Mat4::Translate(Vec3d translate)
	{
		m[12] = translate.x;
		m[13] = translate.y;
		m[14] = translate.z;

		return *this;
	}

	Mat4 Mat4::CreateTranslateMatrix(Vec3d translate)
	{
		Mat4 res;
		res.Identity();
		res.m[12] = translate.x;
		res.m[13] = translate.y;
		res.m[14] = translate.z;

		return res;
	}

	Mat4& Mat4::Scale(float scale)
	{
		m[0] = scale;
		m[5] = scale;
		m[10] = scale;

		return *this;
	}

	Mat4 Mat4::CreateScaleMatrix(float scale)
	{
		Mat4 res;
		res.Identity();
		res.m[0] = scale;
		res.m[5] = scale;
		res.m[10] = scale;

		return res;
	}

	Mat4& Mat4::Scale(Vec3d scale)
	{
		m[0] = scale.x;
		m[5] = scale.y;
		m[10] = scale.z;

		return *this;
	}

	Mat4 Mat4::CreateScaleMatrix(Vec3d scale)
	{
		Mat4 res;
		res.Identity();
		res.m[0] = scale.x;
		res.m[5] = scale.y;
		res.m[10] = scale.z;

		return res;
	}

	Mat4& Mat4::RotateX(float angle)
	{
		float rad = Tools::DegToRad(angle);

		m[5] = cos(rad);
		m[6] = -sin(rad);
		m[9] = sin(rad);
		m[10] = cos(rad);

		return *this;
	}

	Mat4 Mat4::CreateRotateX(float angle)
	{
		float rad = Tools::DegToRad(angle);

		Mat4 res;
		res.Identity();
		res.m[5] = cos(rad);
		res.m[6] = -sin(rad);
		res.m[9] = sin(rad);
		res.m[10] = cos(rad);

		return res;
	}

	Mat4& Mat4::RotateY(float angle)
	{
		float rad = Tools::DegToRad(angle);
		
		m[0] = cos(rad);
		m[2] = sin(rad);
		m[8] = -sin(rad);
		m[10] = cos(rad);

		return *this;
	}

	Mat4 Mat4::CreateRotateY(float angle)
	{
		float rad = Tools::DegToRad(angle);

		Mat4 res;
		res.Identity();

		res.m[0] = cos(rad);
		res.m[2] = sin(rad);
		res.m[8] = -sin(rad);
		res.m[10] = cos(rad);

		return res;
	}

	Mat4& Mat4::RotateZ(float angle)
	{
		float rad = Tools::DegToRad(angle);

		m[0] = cos(rad);
		m[1] = -sin(rad);
		m[4] = sin(rad);
		m[5] = cos(rad);

		return *this;
	}

	Mat4 Mat4::CreateRotateZ(float angle)
	{
		float rad = Tools::DegToRad(angle);

		Mat4 res;
		res.Identity();
		res.m[0] = cos(rad);
		res.m[1] = -sin(rad);
		res.m[4] = sin(rad);
		res.m[5] = cos(rad);

		return res;
	}
	
	Mat4 Mat4::LookAt(Vec3d pos, Vec3d target, Vec3d up)
	{

		Vec3d zaxis = target - pos;
		zaxis.Normalize();
		
		Vec3d xaxis = zaxis.CrossProduct(up);
		xaxis.Normalize();

		Vec3d yaxis = xaxis.CrossProduct(zaxis);

		Mat4 mat;
		mat.Identity();

		mat.m[0] = xaxis.x;							mat.m[1] = yaxis.x;						mat.m[2] = zaxis.x;
		mat.m[4] = xaxis.y;							mat.m[5] = yaxis.y;						mat.m[6] = -zaxis.y;
		mat.m[8] = xaxis.z;							mat.m[9] = yaxis.z;						mat.m[10] = -zaxis.z;
		mat.m[12] = -pos.DotProduct(xaxis);			mat.m[13] = -pos.DotProduct(yaxis);		mat.m[14] = pos.DotProduct(zaxis);

		return mat;
	}

	Mat4 Mat4::Projection(float aspect, float fovy, float near, float far)
	{
		float d = 1.0f / tan(Tools::DegToRad(fovy) / 2.0f);
		float range = 1.0f / (near - far);

		Mat4 projectionMatrix = Mat4(
			d / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, d, 0.0f, 0.0f,
			0.0f, 0.0f, (near + far)*range, -1.0f,
			0.0f, 0.0f, (near*far*2.0f)*range, 0.0f);

		return projectionMatrix;
	}

	Mat4 Mat4::QuatToMatrix(Quat quat)
	{
		Mat4 result = { 1.0f - 2.0f * (quat.y * quat.y) - 2.0f * (quat.z * quat.z), 2.0f * quat.x * quat.y - 2.0f * quat.z * quat.w, 2.0f * quat.x * quat.z + 2.0f * quat.y * quat.w, 0.0f,
						2.0f * quat.x * quat.y + 2.0f * quat.z * quat.w, 1.0f - 2.0f * (quat.x * quat.x) - 2.0f * (quat.z * quat.z), 2.0f * quat.y * quat.z - 2.0f * quat.x * quat.w, 0.0f,
						2.0f * quat.x * quat.z - 2.0f * quat.y * quat.w, 2.0f * quat.y * quat.z + 2.0f * quat.x * quat.w, 1.0f - 2.0f * (quat.x * quat.x) - 2.0f * (quat.y * quat.y), 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f };
		return result.Transposed();
	}
	
	void Mat4::Invert()
	{
		float inv[16];

		inv[0] = m[5] * m[10] * m[15] -
				m[5] * m[11] * m[14] -
				m[9] * m[6] * m[15] +
				m[9] * m[7] * m[14] +
				m[13] * m[6] * m[11] -
				m[13] * m[7] * m[10];

		inv[1] = -m[1] * m[10] * m[15] +
				m[1] * m[11] * m[14] +
				m[9] * m[2] * m[15] -
				m[9] * m[3] * m[14] -
				m[13] * m[2] * m[11] +
				m[13] * m[3] * m[10];

		inv[2] = m[1] * m[6] * m[15] -
				m[1] * m[7] * m[14] -
				m[5] * m[2] * m[15] +
				m[5] * m[3] * m[14] +
				m[13] * m[2] * m[7] -
				m[13] * m[3] * m[6];

		inv[3] = -m[1] * m[6] * m[11] +
				m[1] * m[7] * m[10] +
				m[5] * m[2] * m[11] -
				m[5] * m[3] * m[10] -
				m[9] * m[2] * m[7] +
				m[9] * m[3] * m[6];

		inv[4] = -m[4] * m[10] * m[15] +
				m[4] * m[11] * m[14] +
				m[8] * m[6] * m[15] -
				m[8] * m[7] * m[14] -
				m[12] * m[6] * m[11] +
				m[12] * m[7] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
				m[0] * m[11] * m[14] -
				m[8] * m[2] * m[15] +
				m[8] * m[3] * m[14] +
				m[12] * m[2] * m[11] -
				m[12] * m[3] * m[10];

		inv[6] = -m[0] * m[6] * m[15] +
				m[0] * m[7] * m[14] +
				m[4] * m[2] * m[15] -
				m[4] * m[3] * m[14] -
				m[12] * m[2] * m[7] +
				m[12] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
				m[0] * m[7] * m[10] -
				m[4] * m[2] * m[11] +
				m[4] * m[3] * m[10] +
				m[8] * m[2] * m[7] -
				m[8] * m[3] * m[6];

		inv[8] = m[4] * m[9] * m[15] -
				m[4] * m[11] * m[13] -
				m[8] * m[5] * m[15] +
				m[8] * m[7] * m[13] +
				m[12] * m[5] * m[11] -
				m[12] * m[7] * m[9];

		inv[9] = -m[0] * m[9] * m[15] +
				m[0] * m[11] * m[13] +
				m[8] * m[1] * m[15] -
				m[8] * m[3] * m[13] -
				m[12] * m[1] * m[11] +
				m[12] * m[3] * m[9];

		inv[10] = m[0] * m[5] * m[15] -
				m[0] * m[7] * m[13] -
				m[4] * m[1] * m[15] +
				m[4] * m[3] * m[13] +
				m[12] * m[1] * m[7] -
				m[12] * m[3] * m[5];

		inv[11] = -m[0] * m[5] * m[11] +
				m[0] * m[7] * m[9] +
				m[4] * m[1] * m[11] -
				m[4] * m[3] * m[9] -
				m[8] * m[1] * m[7] +
				m[8] * m[3] * m[5];

		inv[12] = -m[4] * m[9] * m[14] +
				m[4] * m[10] * m[13] +
				m[8] * m[5] * m[14] -
				m[8] * m[6] * m[13] -
				m[12] * m[5] * m[10] +
				m[12] * m[6] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
				m[0] * m[10] * m[13] -
				m[8] * m[1] * m[14] +
				m[8] * m[2] * m[13] +
				m[12] * m[1] * m[10] -
				m[12] * m[2] * m[9];

		inv[14] = -m[0] * m[5] * m[14] +
				m[0] * m[6] * m[13] +
				m[4] * m[1] * m[14] -
				m[4] * m[2] * m[13] -
				m[12] * m[1] * m[6] +
				m[12] * m[2] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
				m[0] * m[6] * m[9] -
				m[4] * m[1] * m[10] +
				m[4] * m[2] * m[9] +
				m[8] * m[1] * m[6] -
				m[8] * m[2] * m[5];

		for (size_t i = 0; i < 16; i++)
			m[i] = inv[i];
	}
	
	Mat4 Mat4::Inverted() const
	{
		float inv[16];

		inv[0] = m[5] * m[10] * m[15] -
				m[5] * m[11] * m[14] -
				m[9] * m[6] * m[15] +
				m[9] * m[7] * m[14] +
				m[13] * m[6] * m[11] -
				m[13] * m[7] * m[10];

		inv[1] = -m[1] * m[10] * m[15] +
				m[1] * m[11] * m[14] +
				m[9] * m[2] * m[15] -
				m[9] * m[3] * m[14] -
				m[13] * m[2] * m[11] +
				m[13] * m[3] * m[10];

		inv[2] = m[1] * m[6] * m[15] -
				m[1] * m[7] * m[14] -
				m[5] * m[2] * m[15] +
				m[5] * m[3] * m[14] +
				m[13] * m[2] * m[7] -
				m[13] * m[3] * m[6];

		inv[3] = -m[1] * m[6] * m[11] +
				m[1] * m[7] * m[10] +
				m[5] * m[2] * m[11] -
				m[5] * m[3] * m[10] -
				m[9] * m[2] * m[7] +
				m[9] * m[3] * m[6];

		inv[4] = -m[4] * m[10] * m[15] +
				m[4] * m[11] * m[14] +
				m[8] * m[6] * m[15] -
				m[8] * m[7] * m[14] -
				m[12] * m[6] * m[11] +
				m[12] * m[7] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
				m[0] * m[11] * m[14] -
				m[8] * m[2] * m[15] +
				m[8] * m[3] * m[14] +
				m[12] * m[2] * m[11] -
				m[12] * m[3] * m[10];

		inv[6] = -m[0] * m[6] * m[15] +
				m[0] * m[7] * m[14] +
				m[4] * m[2] * m[15] -
				m[4] * m[3] * m[14] -
				m[12] * m[2] * m[7] +
				m[12] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
				m[0] * m[7] * m[10] -
				m[4] * m[2] * m[11] +
				m[4] * m[3] * m[10] +
				m[8] * m[2] * m[7] -
				m[8] * m[3] * m[6];

		inv[8] = m[4] * m[9] * m[15] -
				m[4] * m[11] * m[13] -
				m[8] * m[5] * m[15] +
				m[8] * m[7] * m[13] +
				m[12] * m[5] * m[11] -
				m[12] * m[7] * m[9];

		inv[9] = -m[0] * m[9] * m[15] +
				m[0] * m[11] * m[13] +
				m[8] * m[1] * m[15] -
				m[8] * m[3] * m[13] -
				m[12] * m[1] * m[11] +
				m[12] * m[3] * m[9];

		inv[10] = m[0] * m[5] * m[15] -
				m[0] * m[7] * m[13] -
				m[4] * m[1] * m[15] +
				m[4] * m[3] * m[13] +
				m[12] * m[1] * m[7] -
				m[12] * m[3] * m[5];

		inv[11] = -m[0] * m[5] * m[11] +
				m[0] * m[7] * m[9] +
				m[4] * m[1] * m[11] -
				m[4] * m[3] * m[9] -
				m[8] * m[1] * m[7] +
				m[8] * m[3] * m[5];

		inv[12] = -m[4] * m[9] * m[14] +
				m[4] * m[10] * m[13] +
				m[8] * m[5] * m[14] -
				m[8] * m[6] * m[13] -
				m[12] * m[5] * m[10] +
				m[12] * m[6] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
				m[0] * m[10] * m[13] -
				m[8] * m[1] * m[14] +
				m[8] * m[2] * m[13] +
				m[12] * m[1] * m[10] -
				m[12] * m[2] * m[9];

		inv[14] = -m[0] * m[5] * m[14] +
				m[0] * m[6] * m[13] +
				m[4] * m[1] * m[14] -
				m[4] * m[2] * m[13] -
				m[12] * m[1] * m[6] +
				m[12] * m[2] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
				m[0] * m[6] * m[9] -
				m[4] * m[1] * m[10] +
				m[4] * m[2] * m[9] +
				m[8] * m[1] * m[6] -
				m[8] * m[2] * m[5];

		Mat4 mat4 = Mat4();

		for (size_t i = 0; i < 16; i++)
			mat4.m[i] = inv[i];

		return mat4;
	}
	
	void Mat4::Transpose()
	{
		Mat4 mat4 = Mat4();

		mat4.m[0] = m[0];
		mat4.m[1] = m[4];
		mat4.m[2] = m[8];
		mat4.m[3] = m[12];

		mat4.m[4] = m[1];
		mat4.m[5] = m[5];
		mat4.m[6] = m[9];
		mat4.m[7] = m[13];

		mat4.m[8] = m[2];
		mat4.m[9] = m[6];
		mat4.m[10] = m[10];
		mat4.m[11] = m[14];

		mat4.m[12] = m[3];
		mat4.m[13] = m[7];
		mat4.m[14] = m[11];
		mat4.m[15] = m[15];

		for (size_t i = 0; i < 16; i++)
			m[i] = mat4.m[i];
	}

	Mat4 Mat4::Transposed() const
	{
		Mat4 mat4 = Mat4();

		mat4.m[0] = m[0];
		mat4.m[1] = m[4];
		mat4.m[2] = m[8];
		mat4.m[3] = m[12];

		mat4.m[4] = m[1];
		mat4.m[5] = m[5];
		mat4.m[6] = m[9];
		mat4.m[7] = m[13];

		mat4.m[8] = m[2];
		mat4.m[9] = m[6];
		mat4.m[10] = m[10];
		mat4.m[11] = m[14];

		mat4.m[12] = m[3];
		mat4.m[13] = m[7];
		mat4.m[14] = m[11];
		mat4.m[15] = m[15];

		return mat4;
	}
	
	bool Mat4::IsOrthogonal() const
	{
		Mat4 matrix = Mat4();

		for (size_t i = 0; i < 16; ++i)
		{
			matrix.m[i] = m[i];
		}

		std::cout << "--------------------------" << std::endl;

		Mat4 identity;
		identity.Identity();

		Mat4 result = matrix * matrix.Transposed();

		result.LogMatrix();
		identity.LogMatrix();

		for (size_t i = 0; i < 16; ++i)
		{
			if (result.m[i] != identity.m[i])
			{
				return false;
			}
		}

		return true;
	}
	
	void Mat4::LogMatrix() const
	{

		for (size_t line = 0; line < 4; line++)
		{
			std::cout << "|";
			for (size_t column = 0; column < 4; column++)
			{
				std::cout << " " << std::setprecision(3) << m[line + column * 4] << " |";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	
	bool operator==(const Mat4 & mat1, const Mat4 & mat2)
	{
		for (size_t i = 0; i < 16; ++i)
		{
			if (mat1.m[i] == mat2.m[i])
				continue;
			else
				return false;
		}

		return true;
	}

	bool operator!=(const Mat4 &mat1, const Mat4 &mat2)
	{
		return !(mat1 == mat2);
	}
	
	Mat4 operator*(const Mat4& mat1, const Mat4& mat2)
	{
		Mat4 matrix = Mat4();

		for (size_t line = 0; line < 4; line++)
		{
			for (size_t column = 0; column < 4; column++)
			{
				float sum = 0;
				sum += mat1.m[line + 0] * mat2.m[(column * 4) + 0];
				sum += mat1.m[line + 4] * mat2.m[(column * 4) + 1];
				sum += mat1.m[line + 8] * mat2.m[(column * 4) + 2];
				sum += mat1.m[line + 12] * mat2.m[(column * 4) + 3];
				matrix.m[column * 4 + line] = sum;
			}
		}

		return matrix;
	}

	Mat4 operator+=(Mat4 & mat1, const Mat4 & mat2)
	{
		
		return Mat4(mat1.m[0] + mat2.m[0], mat1.m[1] + mat2.m[1], mat1.m[2] + mat2.m[2], mat1.m[3] + mat2.m[3], mat1.m[4] + mat2.m[4], mat1.m[5] + mat2.m[5], mat1.m[6] + mat2.m[6], mat1.m[7] + mat2.m[7], mat1.m[8] + mat2.m[8], mat1.m[9] + mat2.m[9], mat1.m[10] + mat2.m[10], mat1.m[11] + mat2.m[11], mat1.m[12] + mat2.m[12], mat1.m[13] + mat2.m[13], mat1.m[14] + mat2.m[14], mat1.m[15] + mat2.m[15]);
	}

	Vec3d operator*(const Mat4 & mat, const Vec3d & vec)
	{
		return Vec3d(mat.m[0] * vec.x + mat.m[1] * vec.y + mat.m[2] * vec.z + mat.m[3],
			mat.m[4] * vec.x + mat.m[5] * vec.y + mat.m[6] * vec.z + mat.m[7],
			mat.m[8] * vec.x + mat.m[9] * vec.y + mat.m[10] * vec.z + mat.m[11]);
	}
}