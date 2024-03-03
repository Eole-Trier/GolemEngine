#include "Resource/Rendering/shader.h"

#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Debug/log.h"

Shader::Shader() {}

void Shader::SetVertexAndFragmentShader(const char* _vertexPath, const char* _fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(_vertexPath);
        fShaderFile.open(_fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        Log::Print("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    Id = glCreateProgram();
    glAttachShader(Id, vertex);
    glAttachShader(Id, fragment);
    glLinkProgram(Id);
    CheckCompileErrors(Id, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::SetViewPos(Vector3& _viewPos)
{
    SetVec3("viewPos", _viewPos);
}

void Shader::Use()
{
    glUseProgram(Id);
}

void Shader::SetBool(const std::string& _name, bool _value) const
{
    glUniform1i(glGetUniformLocation(Id, _name.c_str()), (int)_value);
}
void Shader::SetInt(const std::string& _name, int _value) const
{
    glUniform1i(glGetUniformLocation(Id, _name.c_str()), _value);
}
void Shader::SetFloat(const std::string& _name, float _value) const
{
    glUniform1f(glGetUniformLocation(Id, _name.c_str()), _value);
}

void Shader::SetVec2(const std::string& _name, const Vector2& _value) const
{
    glUniform2fv(glGetUniformLocation(Id, _name.c_str()), 1, &_value.x);
}
void Shader::SetVec2(const std::string& _name, float _x, float _y) const
{
    glUniform2f(glGetUniformLocation(Id, _name.c_str()), _x, _y);
}
void Shader::SetVec3(const std::string& _name, const Vector3& _value) const
{
    glUniform3fv(glGetUniformLocation(Id, _name.c_str()), 1, &_value.x);
}
void Shader::SetVec3(const std::string& _name, float _x, float _y, float _z) const
{
    glUniform3f(glGetUniformLocation(Id, _name.c_str()), _x, _y, _z);
}
void Shader::SetVec4(const std::string& _name, const Vector4& _value) const
{
    glUniform4fv(glGetUniformLocation(Id, _name.c_str()), 1, &_value.x);
}
void Shader::SetVec4(const std::string& _name, float _x, float _y, float _z, float _w) const
{
    glUniform4f(glGetUniformLocation(Id, _name.c_str()), _x, _y, _z, _w);
}
void Shader::SetMat4(const std::string& _name, const Matrix4& _mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(Id, _name.c_str()), 1, GL_TRUE, &_mat.data[0][0]);
}

void Shader::CheckCompileErrors(unsigned int _shader, std::string _type)
{
    int success;
    char infoLog[1024];
    if (_type != "PROGRAM")
    {
        glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(_shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << _type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(_shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(_shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << _type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}