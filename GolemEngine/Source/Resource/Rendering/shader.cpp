#include "Resource/Rendering/shader.h"

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

Shader::Shader() {}

void Shader::SetVertexFragmentComputeShaders(const char* _vertexPath, const char* _fragmentPath, const char* _computePath)
{
    // Load vertex code
    std::string vertexCode;
    std::ifstream vShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(_vertexPath);
        std::stringstream vShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        vShaderFile.close();
        vertexCode = vShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        Log::Print("ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ\n");
    }

    // Load compute code
    std::string computeCode;
    std::ifstream cShaderFile;
    cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        cShaderFile.open(_computePath);
        std::stringstream cShaderStream;
        cShaderStream << cShaderFile.rdbuf();
        cShaderFile.close();
        computeCode = cShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        Log::Print("ERROR::SHADER::COMPUTE::FILE_NOT_SUCCESFULLY_READ\n");
    }

    // Load fragment code
    std::string fragmentCode;
    std::ifstream fShaderFile;
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        fShaderFile.open(_fragmentPath);
        std::stringstream fShaderStream;
        fShaderStream << fShaderFile.rdbuf();
        fShaderFile.close();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        Log::Print("ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ\n");
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* cShaderCode = computeCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, compute, fragment;

    vertex = GraphicWrapper::CreateShader(SHADER_TYPE_VERTEX);
    GraphicWrapper::SetShaderSourceCode(vertex, 1, &vShaderCode, NULL);
    GraphicWrapper::CompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    compute = GraphicWrapper::CreateShader(SHADER_TYPE_COMPUTE);
    GraphicWrapper::SetShaderSourceCode(compute, 1, &cShaderCode, NULL);
    GraphicWrapper::CompileShader(compute);
    CheckCompileErrors(compute, "COMPUTE");

    fragment = GraphicWrapper::CreateShader(SHADER_TYPE_FRAGMENT);
    GraphicWrapper::SetShaderSourceCode(fragment, 1, &fShaderCode, NULL);
    GraphicWrapper::CompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    id = GraphicWrapper::CreateShaderProgram();
    GraphicWrapper::AttachShaderToProgram(id, vertex);
    GraphicWrapper::AttachShaderToProgram(id, compute);
    GraphicWrapper::AttachShaderToProgram(id, fragment);
    GraphicWrapper::LinkProgram(id);
    CheckCompileErrors(id, "PROGRAM");

    GraphicWrapper::DeleteShaderObject(vertex);
    GraphicWrapper::DeleteShaderObject(compute);
    GraphicWrapper::DeleteShaderObject(fragment);
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