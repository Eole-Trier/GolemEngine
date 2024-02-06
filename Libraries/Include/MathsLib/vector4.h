#pragma once

#include <iostream>


class Matrix4;

class Vector4
{
public:
	float x, y, z, w;

public:
	Vector4();
	~Vector4();
	Vector4(float _x, float _y, float _z, float _w);
	
	float Length() const;
	/* Used for comparing purpose only because doesn't sqrt to make less operations. */
	float LengthSq() const;
	Vector4 Normalize() const;
};

Vector4 operator+(Vector4 _a, float _b);
Vector4 operator-(Vector4 _a, float _b);
Vector4 operator*(Vector4 _a, float _b);
Vector4 operator/(Vector4 _a, float _b);
Vector4 operator+(Vector4 _a, Vector4 _b);
Vector4 operator-(Vector4 _a, Vector4 _b);
bool operator==(Vector4 _a, Vector4 _b);
Vector4 operator*(Matrix4 _a, Vector4 _b);
std::ostream& operator<<(std::ostream& _os, const Vector4& _Vector4);

#include "vector4.inl"