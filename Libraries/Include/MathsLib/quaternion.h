#pragma once

#include <iostream>

#include "dll.h"

class Vector3;

class GOLEM_ENGINE_API Quaternion
{
public:
	float r;
	Vector3 i;

public:
	Quaternion();
	Quaternion(float _real, Vector3 _imaginary);
	~Quaternion();
	
	float Norm();
	Quaternion Normalized();
	Quaternion UnitNorm();
	Quaternion Conjugate();
	Quaternion Inverse();

	GOLEM_ENGINE_API friend Quaternion operator*(Quaternion _q1, Quaternion _q2);
	GOLEM_ENGINE_API friend Quaternion operator/(Quaternion _q1, float _divider);
	GOLEM_ENGINE_API friend bool operator==(Quaternion _q1, Quaternion _q2);
	GOLEM_ENGINE_API friend bool operator!=(Quaternion _q1, Quaternion _q2);

};

