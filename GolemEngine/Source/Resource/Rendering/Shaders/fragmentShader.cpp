#include "Resource/Rendering/Shaders/fragmentShader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Debug/log.h"
#include "Wrappers/graphicWrapper.h"


FragmentShader::FragmentShader(const char* _fragmentPath)
    : fragmentPath(_fragmentPath)
{}

void FragmentShader::SetShader(const char* _fragmentPath)
{
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

    const char* fShaderCode = fragmentCode.c_str();

    unsigned int fragment;

    fragment = GraphicWrapper::CreateShader(SHADER_TYPE_FRAGMENT);
    GraphicWrapper::SetShaderSourceCode(fragment, 1, &fShaderCode, NULL);
    GraphicWrapper::CompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    GraphicWrapper::AttachShaderToProgram(id, fragment);
    GraphicWrapper::LinkProgram(id);
    CheckCompileErrors(id, "PROGRAM");

    GraphicWrapper::DeleteShaderObject(fragment);
}
