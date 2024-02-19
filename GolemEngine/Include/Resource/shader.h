#pragma once

#include <string>

#include "dll.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "resource.h"


class GOLEM_ENGINE_API Shader : public Resource
{
private:
    void CheckCompileErrors(unsigned int shader, std::string type);

public:
    unsigned int Id;

public:
    Shader();
    void SetVertexAndFragmentShader(const char* vertexPath, const char* fragmentPath);
    void SetViewPos(Vector3& viewPos);

    void Use();
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, const Vector2& value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, const Vector3& value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, const Vector4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat4(const std::string& name, const Matrix4& mat) const;
};

