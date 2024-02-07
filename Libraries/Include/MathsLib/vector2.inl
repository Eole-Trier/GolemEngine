#include "matrix2.h"


Vector2::Vector2()
{
}

Vector2::~Vector2()
{
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
} 


Vector2 Vector2::normalize() const
{
	Vector2 temp = { x, y };
	float l = temp.length();
	return Vector2(x / l, y / l);	// temp / l
}

float Vector2::length() const
{
	return sqrtf(x * x + y * y);
}

float Vector2::lengthSquare() const
{
	return (x * x) + (y * y);
}

float Vector2::dist(Vector2 _a, Vector2 _b) const
{
	return (_b - _a).length();
}

/* rotate vector with angle in radians */
Vector2 Vector2::rotate(float _angle) const
{
	//Matrix2 r(2);
	//r.mat = { cosf(_angle), -sinf(_angle), sinf(_angle), cosf(_angle) };
	Matrix2 r = Matrix2::Rotate(_angle);
	Vector2 vec = { x, y };
	Vector2 temp = r * vec;
	return temp;
}

float Vector2::dot(Vector2 _a, Vector2 _b)
{
	return _a.x * _b.x + _a.y * _b.y;
}

Vector2 Vector2::scaleMatrix2(float _sx, float _sy) const
{
	Matrix2 scaleMat2(
		_sx, 0,
		0, _sy
	);
	Vector2 vec = { x, y };
	Vector2 temp = scaleMat2 * vec;
	return temp;
}

/* returns center gravity point of triangle abc */
Vector2 Vector2::isobaryCenterTriangle(Vector2 _a, Vector2 _b, Vector2 _c)
{
	float Xi = (1.f / 3.f) * (_a.x + _b.x + _c.x);
	float Yi = (1.f / 3.f) * (_a.y + _b.y + _c.y);
	return { Xi, Yi };
}

/* returns center point of circle going through all corners of triangle abc*/
Vector2 Vector2::circumcenterTriangle(Vector2 _a, Vector2 _b, Vector2 _c)
{
	float D = 2.f * ( (_a.x * (_b.y - _c.y)) + (_b.x * (_c.y - _a.y)) + (_c.x * (_a.y - _b.y)) );

	float x = 1.f / D * (
		(_a.x * _a.x + (_a.y * _a.y)) * (_b.y - _c.y) +
		(_b.x * _b.x + (_b.y * _b.y)) * (_c.y - _a.y) +
		(_c.x * _c.x + (_c.y * _c.y)) * (_a.y - _b.y)
		);
	float y = 1.f / D * (
		(_a.x * _a.x + (_a.y * _a.y)) * (_c.x - _b.x) +
		(_b.x * _b.x + (_b.y * _b.y)) * (_a.x - _c.x) +
		(_c.x * _c.x + (_c.y * _c.y)) * (_b.x - _a.x)
		);
	return { x, y };
}


#pragma region Operators

Vector2 operator+(Vector2 _a, float _b)
{
	return { _a.x + _b, _a.y + _b };
}

Vector2 operator-(Vector2 _a, float _b)
{
	return { _a.x - _b, _a.y - _b };
}

Vector2 operator*(Vector2 _a, float _s)
{
	return { _a.x * _s, _a.y * _s };
}

Vector2 operator/(Vector2 _a, float _s)
{
	return { _a.x / _s, _a.y / _s };
}

Vector2 operator+(Vector2 _a, Vector2 _b)
{
	return { _a.x + _b.x, _a.y + _b.y };
}

Vector2 operator-(Vector2 _a, Vector2 _b)
{
	return { _a.x - _b.x, _a.y - _b.y };
}

Vector2 operator*(Vector2 _a, Vector2 _b)
{
	return { _a.x * _b.x, _a.y * _b.y };
}

Vector2 operator*(Matrix2 _a, Vector2 _b)
{
	return {
		_a.data[0][0] * _b.x + _a.data[0][1] * _b.y,
		_a.data[1][0] * _b.x + _a.data[1][1] * _b.y
	};
}

bool operator==(Vector2 _a, Vector2 _b)
{
	if (_a.x == _b.x && _a.y == _b.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::ostream& operator<<(std::ostream& _os, const Vector2& _f)
{
	return _os << "{ " << _f.x << " ; " << _f.y << " }";
}

#pragma endregion Operators
