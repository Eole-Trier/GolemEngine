Vector3::Vector3() { }

Vector3::~Vector3() { }

Vector3::Vector3(float _x, float _y, float _z) 
    : x(_x), y(_y), z(_z) { }

Vector3 Vector3::Normalize() const
{
    Vector3 temp = { x, y, z };
    float l = temp.Length();
    return Vector3(x / l, y / l, z / l);	// temp 
}

float Vector3::Length() const
{
    return sqrtf(x * x + y * y + z * z);
}

float Vector3::LengthSq() const
{
    return (x * x) + (y * y) + (z * z);
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

bool operator==(Vector3 _a, Vector3 _b)
{
    return (_a.x == _b.x && _a.y == _b.y && _a.z == _b.z) ? true : false;
}

std::ostream& operator<<(std::ostream& _os, const Vector3& _f)
{
    return _os << "{ " << _f.x << " ; " << _f.y << " ; " << _f.z << " }\n";
}

#pragma endregion Operators