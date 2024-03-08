#include "vector3.h"
#include "quaternion.h"

Vector3::Vector3() { }

Vector3::~Vector3() { }

Vector3::Vector3(float _x, float _y, float _z) 
    : x(_x), y(_y), z(_z) { }


float Vector3::Length() const
{
    return sqrtf(x * x + y * y + z * z);
}

float Vector3::LengthSq() const
{
    return x * x + y * y + z * z;
}

Vector3 Vector3::Normalize() const
{
    float l = Length();
    if (l != 0)
    {
        return Vector3(x / l, y / l, z / l);
    }
    else
    {
        std::cout << "ERROR: Divide by 0 is illegal." << std::endl;
        return Vector3(0, 0, 0);
    }
}

float Vector3::Dot(Vector3 _a, Vector3 _b)
{
    return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
}

Vector3 Vector3::Cross(Vector3 _a, Vector3 _b)
{
    Vector3 temp(
        ((_a.y * _b.z) - (_a.z * _b.y)),
        ((_a.z * _b.x) - (_a.x * _b.z)),
        ((_a.x * _b.y) - (_a.y * _b.x))
    );
    return temp;
}

Vector3 Vector3::RotateVectorAroundAxis(Vector3 _angle)
{
    Quaternion p = Quaternion(0, (*this));

    //create the real quaternion
    Quaternion qX = Quaternion(_angle.x, Vector3(1, 0, 0));
    Quaternion qY = Quaternion(_angle.y, Vector3(0, 1, 0));
    Quaternion qZ = Quaternion(_angle.z, Vector3(0, 0, 1));

    //convert quaternion to unit norm quaternion
    qX = qX.UnitNorm();
    qY = qY.UnitNorm();
    qZ = qZ.UnitNorm();

    //Get the inverse of the quaternion
    Quaternion qXInverse = qX.Inverse();
    Quaternion qYInverse = qY.Inverse();
    Quaternion qZInverse = qZ.Inverse();

    //rotate the quaternion
    Quaternion rotatedVectorX = qX * p * qXInverse;
    Quaternion rotatedVectorY = qY * rotatedVectorX * qYInverse;
    Quaternion rotatedVectorZ = qZ * rotatedVectorY * qZInverse;

    //return the vector part of the quaternion
    return rotatedVectorZ.i;
}

#pragma region Operators

Vector3 operator+(Vector3 _a, float _b)
{
    return { _a.x + _b, _a.y + _b, _a.z + _b };
}

Vector3 operator-(Vector3 _a, float _b)
{
    return { _a.x - _b, _a.y - _b, _a.z - _b };
}

Vector3 operator*(Vector3 _a, float _s)
{
    return { _a.x * _s, _a.y * _s, _a.z * _s };
}

Vector3 operator/(Vector3 _a, float _s)
{
    if (_s == 0.0f)
    {
        std::cout << "ERROR: Divide by 0 is illegal." << std::endl;
        return { 0.0f, 0.0f, 0.0f };
    }
    return { _a.x / _s, _a.y / _s, _a.z / _s };
}

Vector3 operator+(Vector3 _a, Vector3 _b)
{
    return { _a.x + _b.x, _a.y + _b.y, _a.z + _b.z };
}

Vector3 operator-(Vector3 _a, Vector3 _b)
{
    return { _a.x - _b.x, _a.y - _b.y, _a.z - _b.z };
}

bool operator==(Vector3 _a, Vector3 _b)
{
    return (_a.x == _b.x && _a.y == _b.y && _a.z == _b.z) ? true : false;
}

std::ostream& operator<<(std::ostream& _os, const Vector3& _f)
{
    return _os << "{ " << _f.x << " ; " << _f.y << " ; " << _f.z << " }";
}

#pragma endregion Operators