#pragma once

#include "dll.h"


class GOLEM_ENGINE_API Brush
{
public:
    float radius;
    float force;

public:
    Brush();

    void PaintVertex();
    void PaintTexture();
};