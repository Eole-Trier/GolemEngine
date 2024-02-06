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

#pragma endregion Matrix4