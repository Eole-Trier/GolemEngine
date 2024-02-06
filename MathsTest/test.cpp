#include "pch.h"
#include "vector3.h"
#include "vector4.h"

#define EPSILON 0.01f

TEST(TestCaseName, TestName) {
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

TEST(Vector4, Constructor) {
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

#pragma endregion Vector4

#pragma region Matrix4

#pragma endregion Matrix4