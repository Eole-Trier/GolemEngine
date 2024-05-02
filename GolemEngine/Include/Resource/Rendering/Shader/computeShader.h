#pragma once

#include "dll.h"


class GOLEM_ENGINE_API ComputeShader
{
    const char* m_computePath;

public:
    ComputeShader(const char* _computePath);

    void Init();
};