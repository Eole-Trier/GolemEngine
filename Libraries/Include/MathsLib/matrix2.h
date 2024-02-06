#pragma once

#include <iostream>

#include "vector2.h"


class Matrix2 
{
public:
	float data[2][2];

public:
	Matrix2();
	~Matrix2();
	Matrix2(
		float _a, float _b,
		float _c, float _d
	);
	Matrix2(float _number);

	static Matrix2 Identity();
	Matrix2 Transpose();
	Vector2 Diagonal();
	float Trace();
	float Determinant();
	static Matrix2 Rotate(float _angleRad);
	//Matrix2 GaussJordan();
};

Matrix2 operator+(Matrix2 _A, float _n);
Matrix2 operator-(Matrix2 _A, float _n);
Matrix2 operator*(Matrix2 _A, float _s);
Matrix2 operator/(Matrix2 _A, float _s);
Vector2 operator*(Matrix2 _a, Vector2 _b);
Matrix2 operator+(Matrix2 _A, Matrix2 _B);
Matrix2 operator-(Matrix2 _A, Matrix2 _B);
Matrix2 operator*(Matrix2 _A, Matrix2 _B);

std::ostream& operator<<(std::ostream& _os, const Matrix2& _matrix2);

#include "matrix2.inl"
