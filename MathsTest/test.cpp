#include "pch.h"
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

#pragma endregion Vector2

#pragma region Vector3

TEST(Vector3, Constructor) {
	Vector3 v(1.f, 2.f, 3.f);
	EXPECT_NEAR(v.x, 1.f, EPSILON);
	EXPECT_NEAR(v.y, 2.f, EPSILON);
	EXPECT_NEAR(v.z, 3.f, EPSILON);
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

// TODO: Operator_Multiply_Matrix4_Vector4

#pragma endregion Vector4

#pragma region Matrix4

TEST(Matrix4, Constructor)
{
	Matrix4 test = Matrix4(1);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			EXPECT_EQ(test.data[i][j], 1);
	test = Matrix4(0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			EXPECT_EQ(test.data[i][j], i + j);
}

TEST(Matrix4, Identity)
{
	EXPECT_EQ(Matrix4::Identity(), Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
}

TEST(Matrix4, Transpose)
{
	Matrix4 test = Matrix4(2, 6, 7, 3, 2, 0, 4, 0, 9, 2, 43, 2, 7, 1, 3, 98);
	test = test.Transpose();
	EXPECT_EQ(test, Matrix4(2, 2, 9, 7, 6, 0, 2, 1, 7, 4, 43, 3, 3, 0, 2, 98));
}

TEST(Matrix4, Translate)
{
}

TEST(Matrix4, Rotate)
{
}

TEST(Matrix4, Scale)
{
}

TEST(Matrix4, TRS)
{
}

TEST(Matrix4, Projection)
{
}

TEST(Matrix4, LookAt)
{
}

#pragma endregion Matrix4