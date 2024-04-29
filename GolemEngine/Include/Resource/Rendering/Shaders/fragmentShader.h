#pragma once

#include "shader.h"
#include "dll.h"


class GOLEM_ENGINE_API FragmentShader : public Shader
{
public:
    const char* fragmentPath;
    
public:
    FragmentShader(const char* _fragmentPath);

    void SetShader(const char* _shaderPath) override;
};