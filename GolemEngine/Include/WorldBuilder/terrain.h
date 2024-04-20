#pragma once

#include <vector>

#include "Components/transform.h"
#include "Resource/Rendering/shader.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/vertex.h"


class Terrain
{
private:
    Texture* m_texture = nullptr;
    Shader* m_shader = nullptr;
    std::vector<Vertex> m_vertices;
    std::vector<int> m_indices;
    
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
    
public:
    int xResolution;
    int zResolution;
    float generationScale;

public:
    Terrain(int _xResolution, int _zResolution, float _generationScale);

    void SetupMesh();
    void Draw();
};
