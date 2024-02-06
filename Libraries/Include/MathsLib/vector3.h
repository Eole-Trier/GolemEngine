#pragma once
#include <iostream>

class Vector3
{
public:
	float x, y, z;

public:
	Vector3();
	~Vector3();
	Vector3(float _x, float _y, float _z);

	Vector3 Normalize() const;
	float Length() const;
	/* only used to compare for optimization */
	float LengthSq() const;	
	static float Dot(Vector3 _a, Vector3 _b);
	static Vector3 Cross(Vector3 _a, Vector3 _b);
};

Vector3 operator+(Vector3 _a, float b);
Vector3 operator-(Vector3 _a, float b);
Vector3 operator*(Vector3 _a, float b);
Vector3 operator/(Vector3 _a, float b);
Vector3 operator+(Vector3 _a, Vector3 _b);
Vector3 operator-(Vector3 _a, Vector3 _b);
Vector3 operator*(Vector3 _a, Vector3 _b);
Vector3 operator/(Vector3 _a, Vector3 _b);

bool operator==(Vector3 _a, Vector3 _b);
std::ostream& operator<<(std::ostream& os, const Vector3& _vector3);

#include "vector3.inl"