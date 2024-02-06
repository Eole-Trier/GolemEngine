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

	Vector2 normalize() const;
	float length() const;
	float lengthSquare() const;			// only used to compare for optimization
	float dist(Vector2 _a, Vector2 _b) const;
	Vector2 rotate(float _angle) const;
	static float dot(Vector2 _a, Vector2 _b);
	Vector2 scaleMatrix2(float _sx, float _sy) const ;
	static Vector2 isobaryCenterTriangle(Vector2 _a, Vector2 _b, Vector2 _c);
	static Vector2 circumcenterTriangle(Vector2 _a, Vector2 _b, Vector2 _c);
};

Vector2 operator+(Vector2 _a, float _b);
Vector2 operator-(Vector2 _a, float _b);
Vector2 operator*(Vector2 _a, float _b);
Vector2 operator/(Vector2 _a, float _b);
Vector2 operator+(Vector2 _a, Vector2 _b);
Vector2 operator-(Vector2 _a, Vector2 _b);
Vector2 operator*(Matrix2 _a, Vector2 _b);

std::ostream& operator<<(std::ostream& _os, const Vector2& _vector2);

#include "vector2.inl"