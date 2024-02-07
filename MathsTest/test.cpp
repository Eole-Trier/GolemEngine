#include "pch.h"
#include "vector3.h"
#include "vector4.h"

#define EPSILON 0.01f


TEST(TestCaseName, TestName)
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


#pragma region Vector2

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

// TODO: Operator_Multiply_Matrix4_Vector4

#pragma endregion Vector4

#pragma region Matrix4

#pragma endregion Matrix4