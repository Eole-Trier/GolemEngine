#include "pch.h"
#include "vector4.hpp"

#define EPSILON 0.001f

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(Vector4, Constructor)
{
	Vector4 v(1.f, 2.f, 3.f, 4.f);
	EXPECT_NEAR(v.x, 1.f, EPSILON);
}