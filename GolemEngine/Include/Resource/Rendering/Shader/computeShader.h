#pragma once

// #include <string>

#include "dll.h"
#include "Resource/resource.h"


class GOLEM_ENGINE_API ComputeShader : public Resource
{
public:
    unsigned int id = 0;
    std::string m_computePath;

public:
    ComputeShader();

    void Init();
    void Use();

    void SetComputePath(std::string _computePath);
};