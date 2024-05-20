#include "Resource/Rendering/Shader/computeShader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Debug/log.h"
#include "Utils/tools.h"
#include "Wrappers/graphicWrapper.h"


ComputeShader::ComputeShader() {}

void ComputeShader::Init()
{
    std::string computeCode;
    std::ifstream cShaderFile;
    cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        cShaderFile.open(m_computePath);
        std::stringstream cShaderStream;
        cShaderStream << cShaderFile.rdbuf();
        cShaderFile.close();
        computeCode = cShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        Log::Print("ERROR::SHADER::COMPUTE::FILE_NOT_SUCCESFULLY_READ\n");
    }

    const char* cShaderCode = computeCode.c_str();

    unsigned int compute;

    compute = GraphicWrapper::CreateShader(SHADER_TYPE_COMPUTE);
    GraphicWrapper::SetShaderSourceCode(compute, 1, &cShaderCode, NULL);
    GraphicWrapper::CompileShader(compute);
    Tools::CheckCompileErrors(compute, "COMPUTE");

    id = GraphicWrapper::CreateShaderProgram();    // Use a different program than the default shader
    GraphicWrapper::AttachShaderToProgram(id, compute);
    GraphicWrapper::LinkProgram(id);
    Tools::CheckCompileErrors(id, "PROGRAM");

    GraphicWrapper::DeleteShaderObject(compute);
}

void ComputeShader::Use()
{
    GraphicWrapper::UseShader(id);
}

void ComputeShader::SetComputePath(std::string _computePath)
{
    m_computePath = _computePath;
}
