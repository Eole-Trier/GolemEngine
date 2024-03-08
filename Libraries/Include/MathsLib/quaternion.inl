#include <iomanip>

#include "quaternion.h"
#include "vector3.h"
#include "utils.h"

Quaternion::Quaternion() { }

Quaternion::Quaternion(float _real, Vector3 _imaginary)
	:r(_real), i(_imaginary)
{
}

Quaternion::~Quaternion() { }

float Quaternion::Norm()
{
	return sqrt(r * r + i.x * i.x + i.y * i.y + i.z * i.z);
}

Quaternion Quaternion::Normalized()
{
	if ((*this).Norm() == 0)
	{
		std::cout << "ERROR: Norm is = to 0." << std::endl;
		return Quaternion(0, Vector3(0, 0, 0));
	}
	return (*this) / (*this).Norm();
}

Quaternion Quaternion::UnitNorm()
{
	Quaternion q = (*this);
	float angle = DegToRad(q.r);
	q.i = q.i.Normalize();
	q.r = cosf(angle * 0.5);
	q.i = q.i * sinf(angle * 0.5);
	return q;
}

Quaternion Quaternion::Conjugate()
{
	return Quaternion(r, i * (-1));
}

Quaternion Quaternion::Inverse()
{
	float absoluteValue = Norm();
	absoluteValue *= absoluteValue;
	absoluteValue = 1 / absoluteValue;

	Quaternion conjugateValue = Conjugate();

	float scalar = conjugateValue.r * absoluteValue;
	Vector3 imaginary = conjugateValue.i * absoluteValue;

	return Quaternion(scalar, imaginary);
}

#pragma region Operators

Quaternion operator*(Quaternion _q1, Quaternion _q2)
{
	float real = _q1.r * _q2.r - Vector3::Dot(_q1.i, _q2.i);

	Vector3 imaginary = _q2.i * _q1.r + _q1.i * _q2.r + Vector3::Cross(_q1.i, _q2.i);

	return Quaternion(real, imaginary);
}

Quaternion operator/(Quaternion _q1, float _divider)
{
	if (_divider == 0.f)
	{
		std::cout << "ERROR: Divide by 0 is illegal." << std::endl;
		return Quaternion(0, Vector3(0, 0, 0));
	}
	return Quaternion(_q1.r / _divider, _q1.i / _divider);
}

bool operator==(Quaternion _q1, Quaternion _q2)
{
	if (_q1.r != _q2.r || _q1.i != _q2.i)
		return false;
	return true;
}

bool operator!=(Quaternion _q1, Quaternion _q2)
{
	return !(_q1 == _q2);
}

#pragma endregion Operators
