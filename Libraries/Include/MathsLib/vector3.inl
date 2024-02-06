#include "matrix3.hpp"


Vector3::Vector3()
{
}

Vector3::~Vector3()
{
}

Vector3::Vector3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;

}


Vector3 Vector3::normalize() const
{
    Vector3 temp = { x, y, z };
    float l = temp.length();
    return Vector3(x / l, y / l, z / l);	// temp / l
}

float Vector3::length() const
{
    return sqrtf(x * x + y * y + z * z);
}

float Vector3::lengthSq() const
{
    return (x * x) + (y * y) + (z * z);
}

float Vector3::dist(Vector3 _a, Vector3 _b) const
{
    return (_b - _a).length();
}

/* rotate vector with angle in radians */
Vector3 Vector3::rotate(float _XangleRad, float _YangleRad, float _ZangleRad) const
{
    Vector3 temp = { x, y, z };

    Matrix3 rmX = Matrix3::RotateX(_XangleRad);
    Matrix3 rmY = Matrix3::RotateY(_YangleRad);
    Matrix3 rmZ = Matrix3::RotateZ(_ZangleRad);

    Vector3 result = (rmZ * rmY * rmX) * temp;
    return result;
}

float Vector3::dot(Vector3 _a, Vector3 _b)
{
    return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
}

/* Note: I had troubles in the past with this function.The cross product only worked if I calculated it using a matrix,
 * so if weird results occur using cross product, always check here too. 
 */
Vector3 Vector3::cross(Vector3 _a, Vector3 _b)
{
    Vector3 temp(
        ((_a.y * _b.z) - (_a.z * _b.y)),
        ((_a.z * _b.x) - (_a.x * _b.z)),
        ((_a.x * _b.y) - (_a.y * _b.x))
    );
    return temp;
}

Vector3 Vector3::scaleMatrix3(float _sx, float _sy, float _sz) const
{
    Matrix3 scaleMat3(
        _sx, 0, 0,
        0, _sy, 0,
        0, 0, _sz
    );
    Vector3 temp = { x, y, z };
    Vector3 result = scaleMat3 * temp;
    return result;
}


/* returns center gravity point of triangle abc */
Vector3 Vector3::isobaryCenterTriangle(Vector3 _a, Vector3 _b, Vector3 _c)
{
    float Xi = (1.f / 3.f) * (_a.x + _b.x + _c.x);
    float Yi = (1.f / 3.f) * (_a.y + _b.y + _c.y);
    float Zi = (1.f / 3.f) * (_a.z + _b.z + _c.z);
    return { Xi, Yi, Zi };
}

/* returns center point of circle going through all corners of triangle abc*/
Vector3 Vector3::circumcenterTriangle(Vector3 _a, Vector3 _b, Vector3 _c)
{
    // TODO

    //Vector3 P1;
    //Vector3 P2;
    //Vector3 P3;

    //P1.x = a.x;
    //P1.y = a.y;
    //P1.z = a.z;

    //P2.x = b.x;
    //P2.y = b.y;
    //P2.z = b.z;

    //P3.x = c.x;
    //P3.y = c.y;
    //P3.z = c.z;

    //float rNUM = length(P1 - P2) * length(P2 - P3) * length(P3 - P1);
    //float rDENUM = 2 * (length(crossProductVector3(substractVector3(P1, P2), substractVector3(P2, P3))));
    //float r = rNUM / rDENUM;

    //float commomDENUM = 2 * powf(normVector3(crossProductVector3(substractVector3(P1, P2), substractVector3(P2, P3))), 2.0);

    //float alphaNUM = powf(normVector3(substractVector3(P2, P3)), 2.0) * (dotProductVector3(substractVector3(P1, P2), substractVector3(P1, P3)));
    //float alpha = alphaNUM / commomDENUM;

    //float betaNUM = powf(normVector3(substractVector3(P1, P3)), 2.0) * (dotProductVector3(substractVector3(P2, P1), substractVector3(P2, P3)));
    //float beta = betaNUM / commomDENUM;

    //float gammaNUM = powf(normVector3(substractVector3(P1, P2)), 2.0) * (dotProductVector3(substractVector3(P3, P1), substractVector3(P3, P2)));
    //float gamma = gammaNUM / commomDENUM;

    //Point3 toCenter;
    //toCenter.x = alpha * P1.x + beta * P2.x + gamma * P3.x;
    //toCenter.y = alpha * P1.y + beta * P2.y + gamma * P3.y;
    //toCenter.z = alpha * P1.z + beta * P2.z + gamma * P3.z;

    //return toCenter;

    return { 0, 0, 0 };

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
Vector3 operator*(Vector3 _a, Vector3 _b)
{
    return { _a.x * _b.x, _a.y * _b.y, _a.z * _b.z };
}

Vector3 operator*(Matrix3 _a, Vector3 _b)
{
    return {
        _a.data[0][0] * _b.x + _a.data[0][1] * _b.y + _a.data[0][2] * _b.z,
        _a.data[1][0] * _b.x + _a.data[1][1] * _b.y + _a.data[1][2] * _b.z,
        _a.data[2][0] * _b.x + _a.data[2][1] * _b.y + _a.data[2][2] * _b.z
    };
}


std::ostream& operator<<(std::ostream& _os, const Vector3& _f)
{
    return _os << "{ " << _f.x << " ; " << _f.y << " ; " << _f.z << " }\n";
}

#pragma endregion Operators