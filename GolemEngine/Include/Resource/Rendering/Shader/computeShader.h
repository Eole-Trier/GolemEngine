#pragma once

#include "dll.h"


class GOLEM_ENGINE_API ComputeShader
{
public:
    unsigned int id = 0;
    const char* m_computePath;

public:
    ComputeShader(const char* _computePath);

    void Init();
};