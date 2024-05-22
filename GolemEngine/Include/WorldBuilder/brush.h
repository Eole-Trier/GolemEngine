#pragma once


#include "dll.h"


class GOLEM_ENGINE_API Brush
{
public:
    bool isActive = false;
    float radius;
    float force;

public:
    Brush();

    void Update();
};
