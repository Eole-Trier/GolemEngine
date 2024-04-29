#pragma once

#include "shader.h"
#include "dll.h"


class GOLEM_ENGINE_API VertexShader : public Shader
{
public:
    const char* vertexPath;
    
public:
    VertexShader(const char* _vertexPath);

    void SetShader(const char* _shaderPath) override;
};