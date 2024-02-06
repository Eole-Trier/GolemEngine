#pragma once

#include <iostream>

class Matrix3;

class Vector3
{
public:
	float x, y, z;

public:
	Vector3();
	~Vector3();
	Vector3(float _x, float _y, float _z);

	Vector3 normalize() const;
	float length() const;
	float lengthSq() const;	// only used to compare for optimization
	float dist(Vector3 _a, Vector3 _b) const;
	Vector3 rotate(float _XangleRad, float _YangleRad, float _ZangleRad) const;
	static float dot(Vector3 _a, Vector3 _b);
	static Vector3 cross(Vector3 _a, Vector3 _b);
	Vector3 scaleMatrix3(float _sx, float _sy, float _sz) const;
	static Vector3 isobaryCenterTriangle(Vector3 _a, Vector3 _b, Vector3 _c);
	static Vector3 circumcenterTriangle(Vector3 _a, Vector3 _b, Vector3 _c);
};

Vector3 operator+(Vector3 _a, float b);
Vector3 operator-(Vector3 _a, float b);
Vector3 operator*(Vector3 _a, float b);
Vector3 operator/(Vector3 _a, float b);
Vector3 operator+(Vector3 _a, Vector3 _b);
Vector3 operator-(Vector3 _a, Vector3 _b);
Vector3 operator*(Vector3 _a, Vector3 _b);
Vector3 operator*(Matrix3 a, Vector3 _b);

std::ostream& operator<<(std::ostream& os, const Vector3& _vector3);

#include "vector3.inl"