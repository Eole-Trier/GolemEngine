#pragma once

#include "dll.h"


class GOLEM_ENGINE_API Brush
{
private:
    float m_radius;
    float m_force;

public:
    Brush();

    void PaintVertex();
    void PaintTexture();

    float GetRadius();
    float GetForce();
    
    void SetRadius();
    void SetForce();
};