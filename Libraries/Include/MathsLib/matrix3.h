#pragma once

#include <iostream>

#include "vector3.h"


class Matrix3
{
public:
	float data[3][3];

public:
	// Constructors
	Matrix3();
	~Matrix3();
	Matrix3(
		float _a, float _b, float _c,
		float _d, float _e, float _f,
		float _g, float _h, float _i
	);
	Matrix3(float _number);

	Matrix3 Transpose();
	Vector3 Diagonal();
	float Trace();
	float Determinant();
	static Matrix3 RotateX(float _angleRad);
	static Matrix3 RotateY(float _angleRad);
	static Matrix3 RotateZ(float _angleRad);
};

Matrix3 operator+(Matrix3 _A, float _n);
Matrix3 operator-(Matrix3 _A, float _n);
Matrix3 operator*(Matrix3 _A, float _s);
Matrix3 operator/(Matrix3 _A, float _s);
Matrix3 operator+(Matrix3 _A, Matrix3 _B);
Matrix3 operator-(Matrix3 _A, Matrix3 _B);
Matrix3 operator*(Matrix3 _A, Matrix3 _B);

std::ostream& operator<<(std::ostream& _os, const Matrix3& _matrix3);

#include "matrix3.inl"