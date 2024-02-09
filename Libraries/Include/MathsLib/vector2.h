#pragma once

#include <iostream>

class Matrix2;

class Vector2
{
public:
	float x, y;

public:
	Vector2();
	~Vector2();
	Vector2(float _x, float _y);

	Vector2 Normalize() const;
	float Length() const;
	float LengthSq() const;			// only used to compare for optimization
	static float Dot(Vector2 _a, Vector2 _b);
};

Vector2 operator+(Vector2 _a, float _b);
Vector2 operator-(Vector2 _a, float _b);
Vector2 operator*(Vector2 _a, float _b);
Vector2 operator/(Vector2 _a, float _b);
Vector2 operator+(Vector2 _a, Vector2 _b);
Vector2 operator-(Vector2 _a, Vector2 _b);
Vector2 operator*(Matrix2 _a, Vector2 _b);
bool operator==(Vector2 _a, Vector2 _b);

std::ostream& operator<<(std::ostream& _os, const Vector2& _vector2);

#include "vector2.inl"