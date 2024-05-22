#pragma once

// #include <string>

#include "dll.h"
#include "Resource/resource.h"


class ComputeShader : public Resource
{
public:
    unsigned int id = 0;
    std::string m_computePath;

public:
    GOLEM_ENGINE_API ComputeShader();

    GOLEM_ENGINE_API void Init();
    GOLEM_ENGINE_API void Use();

    GOLEM_ENGINE_API void SetComputePath(std::string _computePath);
};