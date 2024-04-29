#include "Resource/Rendering/Shaders/shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Wrappers/graphicWrapper.h"
#include "Debug/log.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"


void Shader::CheckCompileErrors(unsigned int _shader, std::string _type)
{
    int success;
    char infoLog[1024];
    if (_type != "PROGRAM")
    {
        GraphicWrapper::GetShaderIv(_shader, SHADER_COMPILE_STATUS, &success);

        if (!success)
        {
            GraphicWrapper::GetShaderLog(_shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << _type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        GraphicWrapper::GetShaderIv(_shader, SHADER_LINK_STATUS, &success);
        if (!success)
        {
            GraphicWrapper::GetShaderLog(_shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << _type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

Shader::Shader(VertexShader* _vertexShader, FragmentShader* _fragmentShader)
    : vertexShader(_vertexShader), fragmentShader(_fragmentShader)
{
    id = GraphicWrapper::CreateShaderProgram();
}

void Shader::Use()
{
    GraphicWrapper::UseShader(id);
}

void Shader::SetBool(const std::string& _name, bool _value) const
{
    GraphicWrapper::SetShaderBool(id, _name, _value);
}

void Shader::SetInt(const std::string& _name, int _value) const
{
    GraphicWrapper::SetShaderInt(id, _name, _value);
}

void Shader::SetFloat(const std::string& _name, float _value) const
{
    GraphicWrapper::SetShaderFloat(id, _name, _value);
}

void Shader::SetVec2(const std::string& _name, const Vector2& _value) const
{
    GraphicWrapper::SetShaderVec2(id, _name, _value);
}

void Shader::SetVec2(const std::string& _name, float _x, float _y) const
{
    GraphicWrapper::SetShaderVec2(id, _name, _x, _y);
}

void Shader::SetVec3(const std::string& _name, const Vector3& _value) const
{
    GraphicWrapper::SetShaderVec3(id, _name, _value);
}

void Shader::SetVec3(const std::string& _name, float _x, float _y, float _z) const
{
    GraphicWrapper::SetShaderVec3(id, _name, _x, _y, _z);
}

void Shader::SetVec4(const std::string& _name, const Vector4& _value) const
{
    GraphicWrapper::SetShaderVec4(id, _name, _value);
}

void Shader::SetVec4(const std::string& _name, float _x, float _y, float _z, float _w) const
{
    GraphicWrapper::SetShaderVec4(id, _name, _x, _y, _z, _w);
}

void Shader::SetMat4(const std::string& _name, const Matrix4& _value) const
{
    GraphicWrapper::SetShaderMat4(id, _name, _value);
}

void Shader::SetViewPos(Vector3& _viewPos)
{
    SetVec3("viewPos", _viewPos);
}