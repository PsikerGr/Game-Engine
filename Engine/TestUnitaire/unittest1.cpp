#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\MathLib\Tools.h"
#include "..\MathLib\Vec2d.h"
#include "..\MathLib\Vec3d.h"
#include "..\MathLib\Mat4.h"
#include "..\MathLib\Quat.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Maths;

namespace UnitTest
{
	TEST_CLASS(ToolsClass)
	{
	public:

		TEST_METHOD(DegToRad)
		{
			float rad = Tools::DegToRad(10.0f);

			Assert::AreEqual(0.174532935f, rad);
		}

		TEST_METHOD(CompareFloat)
		{
			float a = 5.0f;
			float b = 5.0f;
			float c = 3.0f;

			bool compareFloat = false;
			bool notCompareFloat = false;

			if (Tools::CompareFloat(a, b))
				compareFloat = true;

			if (!Tools::CompareFloat(a, c))
				notCompareFloat = true;

			Assert::IsTrue(compareFloat);
			Assert::IsTrue(notCompareFloat);
		}
	};

	TEST_CLASS(Vector2)
	{
	public:

		TEST_METHOD(Vec2Construct)
		{
			Vec2d vec;

			Assert::AreEqual(0.0f, vec.x);
			Assert::AreEqual(0.0f, vec.y);

			Vec2d vec1(1.0f, 2.0f);

			Assert::AreEqual(1.0f, vec1.x);
			Assert::AreEqual(2.0f, vec1.y);
		}

		TEST_METHOD(Vec2MultiplyScalar)
		{
			Vec2d vec(2.0f, 4.0f);
			Vec2d result = vec * 2.0f;

			Assert::AreEqual(4.0f, result.x);
			Assert::AreEqual(8.0f, result.y);
		}

		TEST_METHOD(Vec2Add)
		{
			Vec2d vec1(1.0f, 5.0f);
			Vec2d vec2(2.0f, 5.0f);
			Vec2d result = vec1 + vec2;

			Assert::AreEqual(3.0f, result.x);
			Assert::AreEqual(10.0f, result.y);
		}

		TEST_METHOD(Vec2AddEqual)
		{
			Vec2d vec1(2.0f, 6.0f);
			vec1 += vec1;

			Assert::AreEqual(4.0f, vec1.x);
			Assert::AreEqual(12.0f, vec1.y);
		}

		TEST_METHOD(Vec2Sub)
		{
			Vec2d vec1(5.0f, 6.0f);
			Vec2d vec2(2.0f, 1.0f);
			Vec2d result = vec1 - vec2;

			Assert::AreEqual(3.0f, result.x);
			Assert::AreEqual(5.0f, result.y);
		}

		TEST_METHOD(Vec2SubEqual)
		{
			Vec2d vec1(2.0f, 5.0f);
			vec1 -= vec1;

			Assert::AreEqual(0.0f, vec1.x);
			Assert::AreEqual(0.0f, vec1.y);
		}

		TEST_METHOD(Vec2Equal)
		{
			Vec2d vec1(1.0f, 5.0f);
			Vec2d vec2(1.0f, 5.0f);

			bool testEqual = false;

			if (vec1 == vec2)
			{
				testEqual = true;
			}

			Assert::IsTrue(testEqual);
		}

		TEST_METHOD(Vec2NotEqual)
		{
			Vec2d vec1(2.0f, 5.0f);
			Vec2d vec2(1.0f, 10.0f);

			bool testNotEqual = false;

			if (vec1 != vec2)
			{
				testNotEqual = true;
			}

			Assert::IsTrue(testNotEqual);
		}

		TEST_METHOD(Vec2Dot)
		{
			Vec2d vec1(2.0f, 3.0f);
			Vec2d vec2(5.0f, 6.0f);
			float result1 = Vec2d::DotProduct(vec1, vec2);
			float result2 = vec1.DotProduct(vec2);

			Assert::AreEqual(28.0f, result1);
			Assert::AreEqual(28.0f, result2);
		}

		TEST_METHOD(Vec2Norm)
		{
			Vec2d vec1(5.0f, 7.0f);
			float result = vec1.Norm();

			Assert::AreEqual(8.60232526704f, result);
		}

		TEST_METHOD(Vec2Normalize)
		{
			Vec2d vec1(5.0f, 7.0f);
			vec1.Normalize();

			Assert::AreEqual(0.58123819371f, vec1.x);
			Assert::AreEqual(0.8137334712f, vec1.y);
		}
	};

	TEST_CLASS(Vector3)
	{
	public:
		
		TEST_METHOD(Vec3Construct)
		{
			Vec3d vec;

			Assert::AreEqual(0.0f, vec.x);
			Assert::AreEqual(0.0f, vec.y);
			Assert::AreEqual(0.0f, vec.z);

			Vec3d vec1(1.0f, 2.0f, 3.0f);

			Assert::AreEqual(1.0f, vec1.x);
			Assert::AreEqual(2.0f, vec1.y);
			Assert::AreEqual(3.0f, vec1.z);
		}

		TEST_METHOD(Vec3MultiplyScalar)
		{
			Vec3d vec(2.0f, 4.0f, 6.0f);
			Vec3d result = vec * 2.0f;

			Assert::AreEqual(4.0f, result.x);
			Assert::AreEqual(8.0f, result.y);
			Assert::AreEqual(12.0f, result.z);
		}

		TEST_METHOD(Vec3Add)
		{
			Vec3d vec1(1.0f, 5.0f, 3.0f);
			Vec3d vec2(2.0f, 5.0f, 2.0f);
			Vec3d result = vec1 + vec2;

			Assert::AreEqual(3.0f, result.x);
			Assert::AreEqual(10.0f, result.y);
			Assert::AreEqual(5.0f, result.z);
		}

		TEST_METHOD(Vec3AddEqual)
		{
			Vec3d vec1(2.0f, 6.0f, 3.0f);
			vec1 += vec1;

			Assert::AreEqual(4.0f, vec1.x);
			Assert::AreEqual(12.0f, vec1.y);
			Assert::AreEqual(6.0f, vec1.z);
		}

		TEST_METHOD(Vec3Sub)
		{
			Vec3d vec1(5.0f, 6.0f, 3.0f);
			Vec3d vec2(2.0f, 1.0f, 2.0f);
			Vec3d result = vec1 - vec2;

			Assert::AreEqual(3.0f, result.x);
			Assert::AreEqual(5.0f, result.y);
			Assert::AreEqual(1.0f, result.z);
		}

		TEST_METHOD(Vec3SubEqual)
		{
			Vec3d vec1(2.0f, 5.0f, 3.0f);
			vec1 -= vec1;

			Assert::AreEqual(0.0f, vec1.x);
			Assert::AreEqual(0.0f, vec1.y);
			Assert::AreEqual(0.0f, vec1.z);
		}

		TEST_METHOD(Vec3Equal)
		{
			Vec3d vec1(1.0f, 5.0f, 3.0f);
			Vec3d vec2(1.0f, 5.0f, 3.0f);

			bool testEqual = false;

			if (vec1 == vec2)
			{
				testEqual = true;
			}

			Assert::IsTrue(testEqual);
		}

		TEST_METHOD(Vec3NotEqual)
		{
			Vec3d vec1(2.0f, 5.0f, 3.0f);
			Vec3d vec2(1.0f, 10.0f, 3.0f);

			bool testNotEqual = false;

			if (vec1 != vec2)
			{
				testNotEqual = true;
			}

			Assert::IsTrue(testNotEqual);
		}

		TEST_METHOD(Vec3Cross)
		{
			Vec3d vec1(2.0f, 3.0f, 4.0f);
			Vec3d vec2(5.0f, 6.0f, 7.0f);
			Vec3d result1 = Vec3d::CrossProduct(vec1, vec2);
			Vec3d result2 = vec1.CrossProduct(vec2);

			Assert::AreEqual(-3.0f, result1.x);
			Assert::AreEqual(6.0f, result1.y);
			Assert::AreEqual(-3.0f, result1.z);

			Assert::AreEqual(-3.0f, result2.x);
			Assert::AreEqual(6.0f, result2.y);
			Assert::AreEqual(-3.0f, result2.z);
		}

		TEST_METHOD(Vec3Dot)
		{
			Vec3d vec1(2.0f, 3.0f, 4.0f);
			Vec3d vec2(5.0f, 6.0f, 7.0f);
			float result1 = Vec3d::DotProduct(vec1, vec2);
			float result2 = vec1.DotProduct(vec2);
			
			Assert::AreEqual(56.0f, result1);
			Assert::AreEqual(56.0f, result2);
		}

		TEST_METHOD(Vec3Norm)
		{
			Vec3d vec1(5.0f, 7.0f, 1.0f);
			float result = vec1.Norm();
			
			Assert::AreEqual(8.66025403784f, result);
		}

		TEST_METHOD(Vec3Normalize)
		{
			Vec3d vec1(5.0f, 7.0f, 1.0f);
			vec1.Normalize();

			Assert::AreEqual(0.57735023971f, vec1.x);
			Assert::AreEqual(0.80829033559f, vec1.y);
			Assert::AreEqual(0.11547004794f, vec1.z);
		}
	};

	TEST_CLASS(Matrix4)
	{
	public:

		TEST_METHOD(Mat4Construct)
		{
			Mat4 mat;

			for (int i = 0; i < 16; i++)
				Assert::AreEqual(0.0f, mat.m[i]);

			Mat4 mat1(0.0f, 1.0f, 2.0f, 3.0f,
					4.0f, 5.0f, 6.0f, 7.0f,
					8.0f, 9.0f, 10.0f, 11.0f,
					12.0f, 13.0f, 14.0f, 15.0f);
			
			Assert::AreEqual(0.0f, mat1.m[0]);
			Assert::AreEqual(1.0f, mat1.m[1]);
			Assert::AreEqual(2.0f, mat1.m[2]);
			Assert::AreEqual(3.0f, mat1.m[3]);
			Assert::AreEqual(4.0f, mat1.m[4]);
			Assert::AreEqual(5.0f, mat1.m[5]);
			Assert::AreEqual(6.0f, mat1.m[6]);
			Assert::AreEqual(7.0f, mat1.m[7]);
			Assert::AreEqual(8.0f, mat1.m[8]);
			Assert::AreEqual(9.0f, mat1.m[9]);
			Assert::AreEqual(10.0f, mat1.m[10]);
			Assert::AreEqual(11.0f, mat1.m[11]);
			Assert::AreEqual(12.0f, mat1.m[12]);
			Assert::AreEqual(13.0f, mat1.m[13]);
			Assert::AreEqual(14.0f, mat1.m[14]);
			Assert::AreEqual(15.0f, mat1.m[15]);

			Mat4 mat2(Vec3d(1.0f, 2.0f, 3.0f), Vec3d(4.0f, 5.0f, 6.0f),
					Vec3d(7.0f, 8.0f, 9.0f), Vec3d(10.0f, 11.0f, 12.0f));

			Assert::AreEqual(1.0f, mat2.m[0]);
			Assert::AreEqual(2.0f, mat2.m[1]);
			Assert::AreEqual(3.0f, mat2.m[2]);
			Assert::AreEqual(0.0f, mat2.m[3]);
			Assert::AreEqual(4.0f, mat2.m[4]);
			Assert::AreEqual(5.0f, mat2.m[5]);
			Assert::AreEqual(6.0f, mat2.m[6]);
			Assert::AreEqual(0.0f, mat2.m[7]);
			Assert::AreEqual(7.0f, mat2.m[8]);
			Assert::AreEqual(8.0f, mat2.m[9]);
			Assert::AreEqual(9.0f, mat2.m[10]);
			Assert::AreEqual(0.0f, mat2.m[11]);
			Assert::AreEqual(10.0f, mat2.m[12]);
			Assert::AreEqual(11.0f, mat2.m[13]);
			Assert::AreEqual(12.0f, mat2.m[14]);
			Assert::AreEqual(1.0f, mat2.m[15]);
		}

		TEST_METHOD(Mat4Equal)
		{
			Mat4 mat1;
			Mat4 mat2;
			mat1.Identity();
			mat2.Identity();

			bool testEqual = false;

			if (mat1 == mat2)
				testEqual = true;

			Assert::IsTrue(testEqual);
		}

		TEST_METHOD(Mat4NotEqual)
		{
			Mat4 mat1;
			Mat4 mat2;
			mat1.Identity();
			mat2.Translate(Vec3d(1.0f, 2.0f, 3.0f));

			bool testNotEqual = false;

			if (mat1 != mat2)
				testNotEqual = true;

			Assert::IsTrue(testNotEqual);
		}

		TEST_METHOD(Mat4Multiply)
		{
			Mat4 mat1(Vec3d(3.0f, 2.0f, 1.0f), Vec3d(4.0f, 5.0f, 6.0f), Vec3d(6.0f, 5.0f, 4.0f), Vec3d(1.0, 2.0f, 3.0f));
			Mat4 mat2(Vec3d(1.0f, 2.0f, 3.0f), Vec3d(7.0f, 8.0f, 9.0f), Vec3d(6.0f, 4.0f, 5.0f), Vec3d(3.0, 2.0f, 1.0f));
			Mat4 result = mat1 * mat2;

			Assert::AreEqual(29.0f, result.m[0]);	Assert::AreEqual(64.0f, result.m[8]);
			Assert::AreEqual(27.0f, result.m[1]);	Assert::AreEqual(57.0f, result.m[9]);
			Assert::AreEqual(25.0f, result.m[2]);	Assert::AreEqual(50.0f, result.m[10]);
			Assert::AreEqual(0.0f, result.m[3]);	Assert::AreEqual(0.0f, result.m[11]);
			Assert::AreEqual(107.0f, result.m[4]);	Assert::AreEqual(24.0f, result.m[12]);
			Assert::AreEqual(99.0f, result.m[5]);	Assert::AreEqual(23.0f, result.m[13]);
			Assert::AreEqual(91.0f, result.m[6]);	Assert::AreEqual(22.0f, result.m[14]);
			Assert::AreEqual(0.0f, result.m[7]);	Assert::AreEqual(1.0f, result.m[15]);
		}

		TEST_METHOD(Mat4MultiplyVec3)
		{
			Vec3d vec(1.0f, 2.0f, 3.0f);
			Mat4 mat(0.0f, 1.0f, 2.0f, 3.0f,
				4.0f, 5.0f, 6.0f, 7.0f,
				8.0f, 9.0f, 10.0f, 11.0f,
				12.0f, 13.0f, 14.0f, 15.0f);

			Vec3d result = mat * vec;

			Assert::AreEqual(11.0f, result.x);
			Assert::AreEqual(39.0f, result.y);
			Assert::AreEqual(67.0f, result.z);
		}

		TEST_METHOD(Mat4Identity)
		{
			Mat4 matrix;
			matrix.Identity();

			for (int i = 0; i <= 15; i++)
			{
				if (i == 0 || i == 5 || i == 10 || i == 15)
					Assert::AreEqual(1.0f, matrix.m[i]);
				else
					Assert::AreEqual(0.0f, matrix.m[i]);
			}
		}

		TEST_METHOD(Mat4Translate)
		{
			Mat4 matrix;
			matrix.Translate(Vec3d(1.0f, 2.0f, 3.0f));
			Mat4 matrix1 = Mat4::CreateTranslateMatrix(Vec3d(2.0f, 3.0f, 4.0f));

			Assert::AreEqual(1.0f, matrix.m[12]);
			Assert::AreEqual(2.0f, matrix.m[13]);
			Assert::AreEqual(3.0f, matrix.m[14]);

			Assert::AreEqual(2.0f, matrix1.m[12]);
			Assert::AreEqual(3.0f, matrix1.m[13]);
			Assert::AreEqual(4.0f, matrix1.m[14]);
		}

		TEST_METHOD(Mat4Scale)
		{
			Mat4 matrix;
			matrix.Scale(Vec3d(2.0f, 2.0f, 3.0f));
			Mat4 matrix1 = Mat4::CreateScaleMatrix(Vec3d(1.0f, 2.0f, 3.0f));

			Assert::AreEqual(2.0f, matrix.m[0]);
			Assert::AreEqual(2.0f, matrix.m[5]);
			Assert::AreEqual(3.0f, matrix.m[10]);

			Assert::AreEqual(1.0f, matrix1.m[0]);
			Assert::AreEqual(2.0f, matrix1.m[5]);
			Assert::AreEqual(3.0f, matrix1.m[10]);

			matrix.Scale(2.0f);
			Mat4 matrix2 = Mat4::CreateScaleMatrix(3.0f);

			Assert::AreEqual(2.0f, matrix.m[0]);
			Assert::AreEqual(2.0f, matrix.m[5]);
			Assert::AreEqual(2.0f, matrix.m[10]);

			Assert::AreEqual(3.0f, matrix2.m[0]);
			Assert::AreEqual(3.0f, matrix2.m[5]);
			Assert::AreEqual(3.0f, matrix2.m[10]);
		}

		TEST_METHOD(Mat4RotateX)
		{
			Mat4 matrix;
			matrix.RotateX(10.0f);
			Mat4 matrix1= Mat4::CreateRotateX(10.0f);

			Assert::AreEqual(0.98480775301f, matrix.m[5]);
			Assert::AreEqual(-0.173648193f, matrix.m[6]);
			Assert::AreEqual(0.173648193f, matrix.m[9]);
			Assert::AreEqual(0.98480775301f, matrix.m[10]);

			Assert::AreEqual(0.98480775301f, matrix1.m[5]);
			Assert::AreEqual(-0.173648193f, matrix1.m[6]);
			Assert::AreEqual(0.173648193f, matrix1.m[9]);
			Assert::AreEqual(0.98480775301f, matrix1.m[10]);
		}

		TEST_METHOD(Mat4RotateY)
		{
			Mat4 matrix;
			matrix.RotateY(10.0f);
			Mat4 matrix1 = Mat4::CreateRotateY(10.0f);
			

			Assert::AreEqual(0.98480775301f, matrix.m[0]);
			Assert::AreEqual(0.173648193f, matrix.m[2]);
			Assert::AreEqual(-0.173648193f, matrix.m[8]);
			Assert::AreEqual(0.98480775301f, matrix.m[10]);

			Assert::AreEqual(0.98480775301f, matrix1.m[0]);
			Assert::AreEqual(0.173648193f, matrix1.m[2]);
			Assert::AreEqual(-0.173648193f, matrix1.m[8]);
			Assert::AreEqual(0.98480775301f, matrix1.m[10]);
		}

		TEST_METHOD(Mat4RotateZ)
		{
			Mat4 matrix;
			matrix.RotateZ(10.0f);
			Mat4 matrix1 = Mat4::CreateRotateZ(10.f);

			Assert::AreEqual(0.98480775301f, matrix.m[0]);
			Assert::AreEqual(-0.173648193f, matrix.m[1]);
			Assert::AreEqual(0.173648193f, matrix.m[4]);
			Assert::AreEqual(0.98480775301f, matrix.m[5]);

			Assert::AreEqual(0.98480775301f, matrix1.m[0]);
			Assert::AreEqual(-0.173648193f, matrix1.m[1]);
			Assert::AreEqual(0.173648193f, matrix1.m[4]);
			Assert::AreEqual(0.98480775301f, matrix1.m[5]);
		}

		TEST_METHOD(Mat4Projection)
		{
			float aspect = (720.0f / 1280.0f);

			Mat4 mat = Mat4::Projection(aspect, 70.0f, 0.1f, 100.0f);

			Assert::AreEqual(2.53892946f, mat.m[0]);
			Assert::AreEqual(0.0f, mat.m[1]);
			Assert::AreEqual(0.0f, mat.m[2]);
			Assert::AreEqual(0.0f, mat.m[3]);
			Assert::AreEqual(0.0f, mat.m[4]);
			Assert::AreEqual(1.42814779f, mat.m[5]);
			Assert::AreEqual(0.0f, mat.m[6]);
			Assert::AreEqual(0.0f, mat.m[7]);
			Assert::AreEqual(0.0f, mat.m[8]);
			Assert::AreEqual(0.0f, mat.m[9]);
			Assert::AreEqual(-1.00200200f, mat.m[10]);
			Assert::AreEqual(-1.0f, mat.m[11]);
			Assert::AreEqual(0.0f, mat.m[12]);
			Assert::AreEqual(0.0f, mat.m[13]);
			Assert::AreEqual(-0.200200200f, mat.m[14]);
			Assert::AreEqual(0.0f, mat.m[15]);
		}

		TEST_METHOD(Mat4QuatToMatrix)
		{

			Quat quat(1.0f, 5.0f, 3.0f, 1.0f);
			Mat4 mat = Mat4::QuatToMatrix(quat);

			Assert::AreEqual(-19.0f, mat.m[0]);
			Assert::AreEqual(28.0f, mat.m[1]);
			Assert::AreEqual(16.0f, mat.m[2]);
			Assert::AreEqual(0.0f, mat.m[3]);
			Assert::AreEqual(32.0f, mat.m[4]);
			Assert::AreEqual(-51.0f, mat.m[5]);
			Assert::AreEqual(-4.0f, mat.m[6]);
			Assert::AreEqual(0.0f, mat.m[7]);
			Assert::AreEqual(4.0f, mat.m[8]);
			Assert::AreEqual(16.0f, mat.m[9]);
			Assert::AreEqual(-67.0f, mat.m[10]);
			Assert::AreEqual(0.0f, mat.m[11]);
			Assert::AreEqual(0.0f, mat.m[12]);
			Assert::AreEqual(0.0f, mat.m[13]);
			Assert::AreEqual(0.0f, mat.m[14]);
			Assert::AreEqual(1.0f, mat.m[15]);
		}

		TEST_METHOD(Mat4Transpose)
		{
			Mat4 matrix(0.0f, 1.0f, 2.0f, 3.0f,
						4.0f, 5.0f, 6.0f, 7.0f,
						8.0f, 9.0f, 10.0f, 11.0f,
						12.0f, 13.0f, 14.0f, 15.0f);

			matrix.Transpose();

			Assert::AreEqual(0.0f, matrix.m[0]);
			Assert::AreEqual(4.0f, matrix.m[1]);
			Assert::AreEqual(8.0f, matrix.m[2]);
			Assert::AreEqual(12.0f, matrix.m[3]);
			Assert::AreEqual(1.0f, matrix.m[4]);
			Assert::AreEqual(5.0f, matrix.m[5]);
			Assert::AreEqual(9.0f, matrix.m[6]);
			Assert::AreEqual(13.f, matrix.m[7]);
			Assert::AreEqual(2.0f, matrix.m[8]);
			Assert::AreEqual(6.0f, matrix.m[9]);
			Assert::AreEqual(10.0f, matrix.m[10]);
			Assert::AreEqual(14.0f, matrix.m[11]);
			Assert::AreEqual(3.0f, matrix.m[12]);
			Assert::AreEqual(7.0f, matrix.m[13]);
			Assert::AreEqual(11.0f, matrix.m[14]);
			Assert::AreEqual(15.0f, matrix.m[15]);

			matrix = matrix.Transposed();

			Assert::AreEqual(0.0f, matrix.m[0]);
			Assert::AreEqual(1.0f, matrix.m[1]);
			Assert::AreEqual(2.0f, matrix.m[2]);
			Assert::AreEqual(3.0f, matrix.m[3]);
			Assert::AreEqual(4.0f, matrix.m[4]);
			Assert::AreEqual(5.0f, matrix.m[5]);
			Assert::AreEqual(6.0f, matrix.m[6]);
			Assert::AreEqual(7.f, matrix.m[7]);
			Assert::AreEqual(8.0f, matrix.m[8]);
			Assert::AreEqual(9.0f, matrix.m[9]);
			Assert::AreEqual(10.0f, matrix.m[10]);
			Assert::AreEqual(11.0f, matrix.m[11]);
			Assert::AreEqual(12.0f, matrix.m[12]);
			Assert::AreEqual(13.0f, matrix.m[13]);
			Assert::AreEqual(14.0f, matrix.m[14]);
			Assert::AreEqual(15.0f, matrix.m[15]);

		}
	
		TEST_METHOD(Mat4Invert)
		{
			Mat4 matrix(3.0f, 3.0f, 3.0f, 0.0f,
						10.0f, 15.0f, 20.0f, 0.0f,
						12.0f, 4.0f, 8.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);

			matrix.Invert();

			Assert::AreEqual(40.0f, matrix.m[0]);
			Assert::AreEqual(-12.0f, matrix.m[1]);
			Assert::AreEqual(15.0f, matrix.m[2]);
			Assert::AreEqual(0.0f, matrix.m[3]);
			Assert::AreEqual(160.0f, matrix.m[4]);
			Assert::AreEqual(-12.0f, matrix.m[5]);
			Assert::AreEqual(-30.0f, matrix.m[6]);
			Assert::AreEqual(0.f, matrix.m[7]);
			Assert::AreEqual(-140.0f, matrix.m[8]);
			Assert::AreEqual(24.0f, matrix.m[9]);
			Assert::AreEqual(15.0f, matrix.m[10]);
			Assert::AreEqual(0.0f, matrix.m[11]);
			Assert::AreEqual(0.0f, matrix.m[12]);
			Assert::AreEqual(0.0f, matrix.m[13]);
			Assert::AreEqual(0.0f, matrix.m[14]);
			Assert::AreEqual(180.0f, matrix.m[15]);

			Mat4 matrix1(3.0f, 3.0f, 3.0f, 0.0f,
				10.0f, 15.0f, 20.0f, 0.0f,
				12.0f, 4.0f, 8.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			matrix1 = matrix1.Inverted();

			Assert::AreEqual(40.0f, matrix.m[0]);
			Assert::AreEqual(-12.0f, matrix.m[1]);
			Assert::AreEqual(15.0f, matrix.m[2]);
			Assert::AreEqual(0.0f, matrix.m[3]);
			Assert::AreEqual(160.0f, matrix.m[4]);
			Assert::AreEqual(-12.0f, matrix.m[5]);
			Assert::AreEqual(-30.0f, matrix.m[6]);
			Assert::AreEqual(0.f, matrix.m[7]);
			Assert::AreEqual(-140.0f, matrix.m[8]);
			Assert::AreEqual(24.0f, matrix.m[9]);
			Assert::AreEqual(15.0f, matrix.m[10]);
			Assert::AreEqual(0.0f, matrix.m[11]);
			Assert::AreEqual(0.0f, matrix.m[12]);
			Assert::AreEqual(0.0f, matrix.m[13]);
			Assert::AreEqual(0.0f, matrix.m[14]);
			Assert::AreEqual(180.0f, matrix.m[15]);
		}

		TEST_METHOD(Mat4Orthogonal)
		{
			Mat4 matrix;
			matrix.Identity();

			bool isOrthogonal = false;

			if (matrix.IsOrthogonal())
			{
				isOrthogonal = true;
			}

			Assert::IsTrue(isOrthogonal);
		}
	};

	TEST_CLASS(Quaternion)
	{
	public:

		TEST_METHOD(QuatConstruct)
		{
			Quat quat;

			Assert::AreEqual(0.0f, quat.w);
			Assert::AreEqual(0.0f, quat.x);
			Assert::AreEqual(0.0f, quat.y);
			Assert::AreEqual(0.0f, quat.z);

			Quat quat1(1.0f, 2.0f, 3.0f, 4.0f);

			Assert::AreEqual(1.0f, quat1.w);
			Assert::AreEqual(2.0f, quat1.x);
			Assert::AreEqual(3.0f, quat1.y);
			Assert::AreEqual(4.0f, quat1.z);
		}

		TEST_METHOD(Quat4Add)
		{
			Quat quat1(1.0f, 5.0f, 3.0f, 1.0f);
			Quat quat2(2.0f, 5.0f, 2.0f, 1.0f);
			Quat result = quat1 + quat2;

			Assert::AreEqual(3.0f, result.w);
			Assert::AreEqual(10.0f, result.x);
			Assert::AreEqual(5.0f, result.y);
			Assert::AreEqual(2.0f, result.z);
		}

		TEST_METHOD(QuatAddEqual)
		{
			Quat quat(2.0f, 6.0f, 3.0f, 1.0f);
			quat += quat;

			Assert::AreEqual(4.0f, quat.w);
			Assert::AreEqual(12.0f, quat.x);
			Assert::AreEqual(6.0f, quat.y);
			Assert::AreEqual(2.0f, quat.z);
		}

		TEST_METHOD(QuatSub)
		{
			Quat quat1(5.0f, 6.0f, 3.0f, 1.0f);
			Quat quat2(2.0f, 1.0f, 2.0f, 1.0f);
			Quat result = quat1 - quat2;

			Assert::AreEqual(3.0f, result.w);
			Assert::AreEqual(5.0f, result.x);
			Assert::AreEqual(1.0f, result.y);
			Assert::AreEqual(0.0f, result.z);
		}

		TEST_METHOD(QuatSubEqual)
		{
			Quat quat(2.0f, 5.0f, 3.0f, 1.0f);
			quat -= quat;

			Assert::AreEqual(0.0f, quat.w);
			Assert::AreEqual(0.0f, quat.x);
			Assert::AreEqual(0.0f, quat.y);
			Assert::AreEqual(0.0f, quat.z);
		}

		TEST_METHOD(QuatEqual)
		{
			Quat quat1(1.0f, 5.0f, 3.0f, 1.0f);
			Quat quat2(1.0f, 5.0f, 3.0f, 1.0f);

			bool testEqual = false;

			if (quat1 == quat2)
			{
				testEqual = true;
			}

			Assert::IsTrue(testEqual);
		}

		TEST_METHOD(QuatNotEqual)
		{
			Quat quat1(2.0f, 5.0f, 3.0f, 1.0f);
			Quat quat2(1.0f, 10.0f, 5.0f, 1.0f);

			bool testNotEqual = false;

			if (quat1 != quat2)
			{
				testNotEqual = true;
			}

			Assert::IsTrue(testNotEqual);
		}

		TEST_METHOD(QuatMultiply)
		{
			Quat quat(1.0f, 2.0f, 3.0f, 4.0f);
			float factor = 5.0f;
			Quat result = quat * factor;

			Assert::AreEqual(5.0f, result.w);
			Assert::AreEqual(10.0f, result.x);
			Assert::AreEqual(15.0f, result.y);
			Assert::AreEqual(20.0f, result.z);
		}

		TEST_METHOD(QuatNorm)
		{
			Quat quat(3.0f, 5.0f, 7.0f, 1.0f);
			float result = quat.Norm();

			Assert::AreEqual(9.16515138991f, result);
		}

		TEST_METHOD(QuatNormalize)
		{
			Quat quat(3.0f, 5.0f, 7.0f, 1.0f);
			quat.Normalize();

			Assert::AreEqual(0.327326834f, quat.w);
			Assert::AreEqual(0.545544684f, quat.x);
			Assert::AreEqual(0.763762593f, quat.y);
			Assert::AreEqual(0.109108940f, quat.z);
		}

		TEST_METHOD(QuatDot)
		{
			Quat quat1(2.0f, 3.0f, 4.0f, 5.0f);
			Quat quat2(6.0f, 7.0f, 8.0f, 9.0f);
			float result1 = Quat::ScalarProduct(quat1, quat2);

			Assert::AreEqual(110.0f, result1);
		}

		TEST_METHOD(QuatLerp)
		{
			Quat quat1(1.0f, 2.0f, 3.0f, 4.0f);
			Quat quat2(2.0f, 6.0f, 7.0f, 8.0f);
			float t = 6.0f;
			Quat result = Quat::Lerp(quat1, quat2, t);

			Assert::AreEqual(7.0f, result.w);
			Assert::AreEqual(26.0f, result.x);
			Assert::AreEqual(27.0f, result.y);
			Assert::AreEqual(28.0f, result.z);
		}

		TEST_METHOD(QuatSlerp)
		{
			Quat quat1(1.0f, 2.0f, 3.0f, 4.0f);
			Quat quat2(2.0f, 6.0f, 7.0f, 8.0f);
			float t = 6.0f;
			Quat result = Quat::Slerp(quat1, quat2, t);

			Assert::AreEqual(0.0153565332f, result.w);
			Assert::AreEqual(0.880009174f, result.x);
			Assert::AreEqual(0.470718026f, result.y);
			Assert::AreEqual(0.0614261329f, result.z);
		}

		TEST_METHOD(QuatNlerp)
		{
			Quat quat1(1.0f, 2.0f, 3.0f, 4.0f);
			Quat quat2(2.0f, 6.0f, 7.0f, 8.0f);
			float t = 6.0f;
			Quat result = Quat::Nlerp(quat1, quat2, t);

			Assert::AreEqual(0.147968054f, result.w);
			Assert::AreEqual(0.549595654f, result.x);
			Assert::AreEqual(0.570733964f, result.y);
			Assert::AreEqual(0.591872215f, result.z);
		}

		TEST_METHOD(QuatAngleToQuat)
		{
			Quat quat(1.0f, 2.0f, 3.0f, 4.0f);
			Vec3d angle(3.0f, 6.0f, 9.0f);

			Quat result = Quat::AngleToQuat(angle);

			Assert::AreEqual(0.995317400f, result.w);
			Assert::AreEqual(0.0769589469f, result.x);
			Assert::AreEqual(0.0301653147f, result.y);
			Assert::AreEqual(0.0501057431f, result.z);
		}
	};
}