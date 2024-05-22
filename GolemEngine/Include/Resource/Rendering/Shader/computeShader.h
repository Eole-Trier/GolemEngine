#pragma once

// #include <string>

#include "dll.h"
#include "Resource/resource.h"

class Vector2;
class Vector3;
class Vector4;
class Matrix4;


class GOLEM_ENGINE_API ComputeShader : public Resource
{
public:
    unsigned int id = 0;
    std::string m_computePath;

public:
    ComputeShader();

    void Init();
    void Use();

    void SetComputePath(std::string _computePath);

    void SetBool(const std::string& _name, bool _value) const;
    void SetInt(const std::string& _name, int _value) const;
    void SetFloat(const std::string& _name, float _value) const;
    void SetVec2(const std::string& _name, const Vector2& _value) const;
    void SetVec2(const std::string& _name, float _x, float _y) const;
    void SetVec3(const std::string& _name, const Vector3& _value) const;
    void SetVec3(const std::string& _name, float _x, float _y, float _z) const;
    void SetVec4(const std::string& _name, const Vector4& _value) const;
    void SetVec4(const std::string& _name, float _x, float _y, float _z, float _w) const;
    void SetMat4(const std::string& _name, const Matrix4& _mat) const;
};