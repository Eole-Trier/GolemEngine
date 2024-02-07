#pragma once

#include <iostream>

#include "vector3.h"


class Matrix4
{
public:
	float data[4][4];

public:
	Matrix4();
	~Matrix4();
	Matrix4(
		float _a, float _b, float _c, float _d,
		float _e, float _f, float _g, float _h,
		float _i, float _j, float _k, float _l,
		float _m, float _n, float _o, float _p
	);
	Matrix4(float _number);

	static Matrix4 Identity();
	Matrix4 Transpose();
	Matrix4 Translate(Vector3 _t);
	Matrix4 Rotate(Vector3 _XYZrad);
	Matrix4 Scale(Vector3 _s);
	Matrix4 TRS(Vector3 _translate, Vector3 _rotate, Vector3 _scale);
	static Matrix4 Projection(float _fov, float _aspectRatio, float _zNear, float _zFar);
	static Matrix4 LookAt(Vector3 _cameraPos, Vector3 _targetPos, Vector3 _up);
};

Matrix4 operator+(Matrix4 _A, float _n);
Matrix4 operator-(Matrix4 _A, float _n);
Matrix4 operator*(Matrix4 _A, float _s);
Matrix4 operator/(Matrix4 _A, float _s);
Matrix4 operator+(Matrix4 _A, Matrix4 _B);
Matrix4 operator-(Matrix4 _A, Matrix4 _B);
Matrix4 operator*(Matrix4 _A, Matrix4 _B);

bool operator==(Matrix4 _A, Matrix4 _B);
bool operator!=(Matrix4 _A, Matrix4 _B);

std::ostream& operator<<(std::ostream& _os, const Matrix4& _matrix4);

#include "matrix4.inl"