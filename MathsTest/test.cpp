#include "pch.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "utils.h"

#define EPSILON 0.01f


TEST(TestCaseName, TestName)
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

#pragma region Vector2

namespace testVec2
{
	Vector2 vec1(1, 1);
	Vector2 vec2(2, 2);
	float sx = 2.f;
	float sy = 2.f;
	Matrix2 mat(1);

	TEST(Vector2, Normalize)
	{
		EXPECT_NEAR(vec1.normalize().x, 0.707107, EPSILON);
		EXPECT_NEAR(vec1.normalize().y, 0.707107, EPSILON);
	}

	TEST(Vector2, length)
	{
		EXPECT_NEAR(vec1.length(), 1.41421, EPSILON);
	}

	TEST(Vector2, lengthSquare)
	{
		EXPECT_NEAR(vec1.lengthSquare(), 2, EPSILON);
	}

	TEST(Vector2, distance)
	{
		EXPECT_NEAR(vec1.dist(vec1, vec2), 1.41421, EPSILON);
	}

	TEST(Vector2, Rotate)
	{
		EXPECT_NEAR(vec1.rotate(M_PI / 4).x, 1.41421, EPSILON);
		EXPECT_NEAR(vec1.rotate(M_PI / 4).y, 0, EPSILON);
	}

	TEST(Vector2, DotProduct)
	{
		EXPECT_EQ(vec1.dot(vec1, vec2), 4);
	}

	TEST(Vector2, scale)
	{
		EXPECT_FLOAT_EQ(vec1.scaleMatrix2(sx, sy).x, 2.f);
		EXPECT_FLOAT_EQ(vec1.scaleMatrix2(sx, sy).y, 2.f);
	}

	TEST(Vector2, Operators)
	{
		EXPECT_EQ(vec1 + vec2, Vector2(3, 3));

		EXPECT_EQ(vec1 - vec2, Vector2(-1, -1));

		EXPECT_EQ(vec1 * vec2, Vector2(2, 2));

		EXPECT_EQ(vec1 / sx, Vector2(0.5, 0.5));

		EXPECT_EQ(vec1 * sx, Vector2(2, 2));

		EXPECT_EQ(vec1 + sx, Vector2(3, 3));

		EXPECT_EQ(vec1 - sx, Vector2(-1, -1));

		EXPECT_EQ(mat * vec1, Vector2(2, 2));
	}
}

#pragma endregion Vector2

#pragma region Vector3

TEST(Vector3, Constructor) 
{
	Vector3 v(1.f, 2.f, 3.f);
	EXPECT_NEAR(v.x, 1.f, EPSILON);
	EXPECT_NEAR(v.y, 2.f, EPSILON);
	EXPECT_NEAR(v.z, 3.f, EPSILON);
}

TEST(Vector3, Length) 
{
	Vector3 v(1.f, 2.f, 3.f);
	EXPECT_NEAR(v.Length(), 3.74166f, EPSILON);
}

TEST(Vector3, LengthSq) 
{
	Vector3 v(1.f, 2.f, 3.f);
	EXPECT_NEAR(v.LengthSq(), 14.0f, EPSILON);
}

TEST(Vector3, Normalize) {
	Vector3 a(1.0f, 2.0f, 3.0f);
	EXPECT_NEAR(a.Normalize().x, 0.27f, EPSILON);
	EXPECT_NEAR(a.Normalize().y, 0.53f, EPSILON);
	EXPECT_NEAR(a.Normalize().z, 0.80f, EPSILON);
}

TEST(Vector3, Dot) {
	Vector3 a(1.0f, 2.0f, 3.0f);
	Vector3 b(3.0f, 2.0f, 1.0f);
	EXPECT_EQ(Vector3::Dot(a, b), 10.0f);
}

TEST(Vector3, Cross) {
	Vector3 a(1.0f, 2.0f, 3.0f);
	Vector3 b(3.0f, 2.0f, 1.0f);
	Vector3 c(-4.0f, 8.0f, -4.0f);
	EXPECT_NEAR(Vector3::Cross(a, b).x, c.x, EPSILON);
	EXPECT_NEAR(Vector3::Cross(a, b).y, c.y, EPSILON);
	EXPECT_NEAR(Vector3::Cross(a, b).z, c.z, EPSILON);
}

TEST(Vector3, Operator_NotEqual_Vector3)
{
	Vector3 a(1.f, 2.f, 3.f);
	Vector3 b(-0.f, 1.f, -4.9f);
	EXPECT_NE(a.x, b.x);
	EXPECT_NE(a.y, b.y);
	EXPECT_NE(a.z, b.z);
}
#pragma endregion Vector3

#pragma region Vector4

TEST(Vector4, Constructor)
{
	Vector4 v(1.f, 2.f, 3.f, 4.f);
	EXPECT_NEAR(v.x, 1.f, EPSILON);
	EXPECT_NEAR(v.y, 2.f, EPSILON);
	EXPECT_NEAR(v.z, 3.f, EPSILON);
	EXPECT_NEAR(v.w, 4.f, EPSILON);
}

TEST(Vector4, Length)
{
	Vector4 v(1.f, 2.f, 3.f, 4.f);
	EXPECT_NEAR(v.Length(), 5.47f, EPSILON);
}

TEST(Vector4, LenghtSq)
{
	Vector4 v(1.f, 2.f, 3.f, 4.f);
	EXPECT_NEAR(v.LengthSq(), 30.f, EPSILON);
}

TEST(Vector4, Normalize)
{
	Vector4 v(1.f, 2.f, 3.f, 4.f);
	EXPECT_NEAR(v.Normalize().x, 0.18f, EPSILON);
	EXPECT_NEAR(v.Normalize().y, 0.36f, EPSILON);
	EXPECT_NEAR(v.Normalize().z, 0.54f, EPSILON);
	EXPECT_NEAR(v.Normalize().w, 0.73f, EPSILON);
}

TEST(Vector4, Operator_Add_Float)
{
	Vector4 a(1.f, 2.f, 3.f, 4.f);
	Vector4 b = a + 3.78f;
	EXPECT_NEAR(b.x, 4.78f, EPSILON);
	EXPECT_NEAR(b.y, 5.78f, EPSILON);
	EXPECT_NEAR(b.z, 6.78f, EPSILON);
	EXPECT_NEAR(b.w, 7.78f, EPSILON);
}

TEST(Vector4, Operator_Substract_Float)
{
	Vector4 a(1.f, 2.f, 3.f, 4.f);
	Vector4 b = a - 3.78f;
	EXPECT_NEAR(b.x, -2.78f, EPSILON);
	EXPECT_NEAR(b.y, -1.78f, EPSILON);
	EXPECT_NEAR(b.z, -0.78f, EPSILON);
	EXPECT_NEAR(b.w, 0.22f, EPSILON);
}

TEST(Vector4, Operator_Multiply_Float)
{
	Vector4 a(1.f, 2.f, 3.f, 4.f);
	Vector4 b = a * 3.78f;
	EXPECT_NEAR(b.x, 3.78f, EPSILON);
	EXPECT_NEAR(b.y, 7.56f, EPSILON);
	EXPECT_NEAR(b.z, 11.34f, EPSILON);
	EXPECT_NEAR(b.w, 15.12f, EPSILON);
}

TEST(Vector4, Operator_Divide_Float)
{
	Vector4 a(1.f, 2.f, 3.f, 4.f);
	Vector4 b = a / 3.78f;
	EXPECT_NEAR(b.x, 0.26f, EPSILON);
	EXPECT_NEAR(b.y, 0.52f, EPSILON);
	EXPECT_NEAR(b.z, 0.79f, EPSILON);
	EXPECT_NEAR(b.w, 1.05f, EPSILON);
}

TEST(Vector4, Operator_Add_Vector4)
{
	Vector4 a(1.f, 2.f, 3.f, 4.f);
	Vector4 b(3.5f, 2.f, -1.5f, 0.78f);
	EXPECT_NEAR((a + b).x, 4.5f, EPSILON);
	EXPECT_NEAR((a + b).y, 4.f, EPSILON);
	EXPECT_NEAR((a + b).z, 1.5f, EPSILON);
	EXPECT_NEAR((a + b).w, 4.78f, EPSILON);
}

TEST(Vector4, Operator_Substract_Vector4)
{
	Vector4 a(1.f, 2.f, 3.f, 4.f);
	Vector4 b(3.5f, 2.f, -1.5f, 0.78f);
	EXPECT_NEAR((a - b).x, -2.5f, EPSILON);
	EXPECT_NEAR((a - b).y, 0.f, EPSILON);
	EXPECT_NEAR((a - b).z, 4.5f, EPSILON);
	EXPECT_NEAR((a - b).w, 3.22f, EPSILON);
}

TEST(Vector4, Operator_Equal_Vector4)
{
	Vector4 a(1.f, -0.f, 3.f, -4.9f);
	Vector4 b(1.f, -0.f, 3.f, -4.9f);
	EXPECT_EQ(a.x, b.x);
	EXPECT_EQ(a.y, b.y);
	EXPECT_EQ(a.z, b.z);
	EXPECT_EQ(a.z, b.z);
}

TEST(Vector4, Operator_NotEqual_Vector4)
{
	Vector4 a(1.f, 2.f, 3.f, -4.9f);
	Vector4 b(-0.f, 1.f, -4.9f, 2.5f);
	EXPECT_NE(a.x, b.x);
	EXPECT_NE(a.y, b.y);
	EXPECT_NE(a.z, b.z);
	EXPECT_NE(a.w, b.w);
}

TEST(Vector4, Operator_Multiply_Matrix_Vector)
{
	Vector4 a(1.f, 2.f, 3.f, -4.9f);
	Matrix4 b(2.9f, 1, -2, -3.5f, 0, 0.5f, -0.78f, 2.3f, 4, 6, 3, 75, 1, -67, 4, 32);
	EXPECT_NEAR((b * a).x, 16.05f, EPSILON);
	EXPECT_NEAR((b * a).y, -12.61f, EPSILON);
	EXPECT_NEAR((b * a).z, -342.5f, EPSILON);
	EXPECT_NEAR((b * a).w, -277.8f, EPSILON);
}

#pragma endregion Vector4

#pragma region Matrix4

TEST(Matrix4, Constructor)
{
	Matrix4 test = Matrix4(1);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			EXPECT_EQ(test.data[i][j], 1);
	test = Matrix4(0.f, 1.f, 2.f, 3.f, 1.f, 2.f, 3.f, 4.f, 2.f, 3.f, 4.f, 5.f, 3.f, 4.f, 5.f, 6.f);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			EXPECT_EQ(test.data[i][j], i + j);
}

TEST(Matrix4, Identity)
{
	EXPECT_EQ(Matrix4::Identity(), Matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f));
}

TEST(Matrix4, Transpose)
{
	Matrix4 test = Matrix4(-2.f, 6.f, 7.f, 3.f, 2.f, 0.f, 4.f, 0.f, 9.f, 2.f, 43.f, 2.f, 7.f, 1.f, 3.f, 98.2f);
	test = test.Transpose();
	EXPECT_EQ(test, Matrix4(-2.f, 2.f, 9.f, 7.f, 6.f, 0.f, 2.f, 1.f, 7.f, 4.f, 43.f, 3.f, 3.f, 0.f, 2.f, 98.2f));
}

TEST(Matrix4, Translate)
{
	Matrix4 test = Matrix4(-2.f, 6.f, 7.f, 3.f, 2.f, 0.f, 4.f, 0.f, 9.f, 2.f, 43.f, 2.f, 7.f, 1.f, 3.f, 98.2f);
	test = test.Translate(Vector3(10.f, -5.f, 3.1f));
	EXPECT_EQ(test, Matrix4(-2.f, 6.f, 7.f, -25.3000011f, 2.f, 0.f, 4.f, 32.4000015f, 9.f, 2.f, 43.f, 215.300003f, 7.f, 1.f, 3.f, 172.5f)); //precision float 
}

TEST(Matrix4, Rotate)
{
	Matrix4 test = Matrix4(-2.f, 6.f, 7.f, 3.f, 2.f, 0.f, 4.f, 0.f, 9.f, 2.f, 43.f, 2.f, 7.f, 1.f, 3.f, 98.2f);
	test = test.Rotate(Vector3(3.14f, 3.14f/2.f, -3.14f / 2.f));
	EXPECT_EQ(test, Matrix4(-7.00478f, 1.98567f, 5.99919f, 3, -4, -1.99999f, -0.00796273f, 0, -43.0016f, -9.0047f, 1.94425f, 2, -3.00079f, -7.00237f, 0.980886f, 98.2f)); //precision float 
}

TEST(Matrix4, Scale)
{
	Matrix4 test = Matrix4(-2, 5, 3, 2, 10, 5.5f, 6, 1, 1, 2, 1, 3, 2, 46, 20, 5);
	test = test.Scale(Vector3(2, -4, 1.5f));
	EXPECT_EQ(test, Matrix4(-4, -20, 4.5f, 2, 20, -22, 9, 1, 2, -8, 1.5f, 3, 4, -184, 30, 5));
}

TEST(Matrix4, TRS)
{
	Matrix4 test = Matrix4::Identity();
	test = test.TRS(Vector3(10.f, -5.f, 3.5f), Vector3(3.14f, 3.14f / 2.f, -3.14f / 2.f), Vector3(2, -4, 1.5f));
	EXPECT_EQ(test, Matrix4(0.0000012681f, 3.99998879f, -0.00358323079f, 10, -0.00159254810f, 0.00955528114f, 1.49999535f, -5, -1.99999940f, -0.00000507242, -0.00119440991f, 3.5f, 0, 0, 0, 1));
}

TEST(Matrix4, Projection)
{
	Matrix4 test = Matrix4::Projection(1.57079637f, 800.f / 600.f, 0.100000001f, 100);
	EXPECT_EQ(test, Matrix4(0.75f, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1.00200200, -0.200200200, 0, 0, -1, 0));
}

TEST(Matrix4, LookAt)
{
	Matrix4 test = Matrix4::LookAt(Vector3(0, 0, 5), Vector3(0, 0, -1), Vector3(0, 1, 0));
	EXPECT_EQ(test, Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, -5, 0, 0, 0, 1));
}

TEST(Matrix4, FloatOperatorAdd)
{
	Matrix4 test = Matrix4(1.f, 2.f, 3.f, -4.f, 5.f, 2.5f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
	test = test + 5;
	EXPECT_EQ(test, Matrix4(6.f, 7.f, 8.f, 1.f, 10.f, 7.5f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f, 19.f, 20.f));
}

TEST(Matrix4, FloatOperatorSubstract)
{
	Matrix4 test = Matrix4(1.f, 2.f, 3.f, -4.f, 5.f, 2.5f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
	test = test - 5;
	EXPECT_EQ(test, Matrix4(-4.f, -3.f, -2.f, -9.f, 0.f, -2.5f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f));
}

TEST(Matrix4, FloatOperatorMultiply)
{
	Matrix4 test = Matrix4(1.f, 2.f, 3.f, -4.f, 5.f, 2.5f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
	test = test * 3;
	EXPECT_EQ(test, Matrix4(3.f, 6.f, 9.f, -12.f, 15.f, 7.5f, 18.f, 21.f, 24.f, 27.f, 30.f, 33.f, 36.f, 39.f, 42.f, 45.f));
}

TEST(Matrix4, FloatOperatorDivide)
{
	Matrix4 test = Matrix4(1.f, 2.f, 4.f, -4.f, 5.f, 3.f, 6.f, 8.f, 10.f, 12.f, 16.f, 20.f, 24.f, 28.f, 32.f, 36.f);
	test = test / 4;
	EXPECT_EQ(test, Matrix4(0.25f, 0.5f, 1.f, -1.f, 1.25f, 0.75f, 1.5f, 2.f, 2.5f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f));
}

TEST(Matrix4, MatOperatorAdd)
{
	Matrix4 test1 = Matrix4(1.f, 2.f, 4.f, -4.f, 5.f, 3.f, 6.f, 8.f, 10.f, 12.f, 16.f, 20.f, 24.f, 28.f, 32.f, 36.f);
	Matrix4 test2 = Matrix4(-1.f, -2.f, -4.f, 4.f, -5.f, -3.f, -6.f, -8.f, -10.f, -12.f, -16.f, -20.f, -24.f, -28.f, -32.f, -36.f);
	test1 = test1 + test2;
	EXPECT_EQ(test1, Matrix4(0));
}

TEST(Matrix4, MatOperatorSubstract)
{
	Matrix4 test = Matrix4(1.f, 2.f, 4.f, -4.f, 5.f, 3.f, 6.f, 8.f, 10.f, 12.f, 16.f, 20.f, 24.f, 28.f, 32.f, 36.f);
	test = test - test;
	EXPECT_EQ(test, Matrix4(0));
}

TEST(Matrix4, MatOperatorMultiply)
{
	Matrix4 test = Matrix4(1.f, 2.f, 4.f, -4.f, 5.f, 3.f, 6.f, 8.f, 10.f, 12.f, 16.f, 20.f, 24.f, 28.f, 32.f, 36.f);
	test = test * test;
	EXPECT_EQ(test, Matrix4(-45, -56, -48, -52, 272, 315, 390, 412, 710, 808, 1008, 1096, 1348, 1524, 1928, 2064));
}

TEST(Matrix4, MatOperatorEqual)
{
	Matrix4 test1 = Matrix4(1.f, 2.f, 4.f, -4.f, 5.f, 3.f, 6.f, 8.f, 10.f, 12.f, 16.f, 20.f, 24.f, 28.f, 32.f, 36.f);
	Matrix4 test2 = Matrix4(1.f, 2.f, 4.f, -4.f, 5.f, 3.f, 6.f, 8.f, 10.f, 12.f, 16.f, 20.f, 24.f, 28.f, 32.f, 36.f);
	EXPECT_EQ(test1, test2);
}

TEST(Matrix4, MatOperatorNotEqual)
{
	Matrix4 test1 = Matrix4(1.f, 2.f, 4.f, -4.f, 5.f, 3.f, 6.f, 8.f, 10.f, 12.f, 16.f, 20.f, 24.f, 28.f, 32.f, 36.f);
	Matrix4 test2 = Matrix4(1.f, 2.f, 4.f, -4.f, 5.f, 3.f, 6.f, 8.f, 10.f, 12.f, 16.f, 20.f, 24.f, 28.f, 0.f, 36.f);
	EXPECT_NE(test1, test2);
}

#pragma endregion Matrix4