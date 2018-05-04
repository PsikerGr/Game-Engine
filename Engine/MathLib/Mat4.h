#pragma once


namespace Maths
{
	struct Quat;
	struct Vec3d;

	struct Mat4
	{
		Mat4();
		Mat4(float _m[16]);
		Mat4(float m0, float m1, float m2, float m3, float m4, float m5, 
			 float m6, float m7, float m8, float m9, float m10, float m11, 
			 float m12, float m13, float m14, float m15);
		Mat4(const Vec3d right , const Vec3d up, const Vec3d forward, const Vec3d position);
	
		~Mat4() = default;

		float	m[16];

		Mat4 Identity();

		Mat4& Translate(Vec3d translate);
		static Mat4 CreateTranslateMatrix(Vec3d translate);

		Mat4& Scale(float scale);
		static Mat4 CreateScaleMatrix(float scale);
		Mat4& Scale(Vec3d spaceVector);
		static Mat4 CreateScaleMatrix(Vec3d spaceVector);

		Mat4& RotateX(float angle);
		static Mat4 CreateRotateX(float angle);
		Mat4& RotateY(float angle);
		static Mat4 CreateRotateY(float angle);
		Mat4& RotateZ(float angle);
		static Mat4 CreateRotateZ(float angle);

		static Mat4 LookAt(Vec3d pos, Vec3d target, Vec3d up);
		static Mat4	Projection(float aspect, float fovy, float near, float far);
		static Mat4 QuatToMatrix(Quat quat);
		
		void Invert();
		Mat4 Inverted() const;
		void Transpose();
		Mat4 Transposed() const;

		bool IsOrthogonal() const;

		void LogMatrix() const;
	};

	bool operator==(const Mat4 &mat1, const Mat4 &mat2);
	bool operator!=(const Mat4 &mat1, const Mat4 &mat2);
	Mat4 operator*(const Mat4 &mat1, const Mat4& mat2);
	Mat4 operator+=(Mat4 &mat1, const Mat4& mat2);
	Vec3d operator*(const Mat4& mat, const Vec3d& vec);
}