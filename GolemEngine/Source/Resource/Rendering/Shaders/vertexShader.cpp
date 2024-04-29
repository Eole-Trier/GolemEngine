#include "Resource/Rendering/Shaders/vertexShader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Debug/log.h"
#include "Wrappers/graphicWrapper.h"


VertexShader::VertexShader(const char* _vertexPath)
    : vertexPath(_vertexPath)
{}

void VertexShader::SetShader()
{
    // Load vertex code
    std::string vertexCode;
    std::ifstream vShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        std::stringstream vShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        vShaderFile.close();
        vertexCode = vShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        Log::Print("ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ\n");
    }

    const char* vShaderCode = vertexCode.c_str();

    unsigned int vertex;

    vertex = GraphicWrapper::CreateShader(SHADER_TYPE_VERTEX);
    GraphicWrapper::SetShaderSourceCode(vertex, 1, &vShaderCode, NULL);
    GraphicWrapper::CompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    GraphicWrapper::AttachShaderToProgram(id, vertex);
    GraphicWrapper::LinkProgram(id);
    CheckCompileErrors(id, "PROGRAM");

    GraphicWrapper::DeleteShaderObject(vertex);
}
