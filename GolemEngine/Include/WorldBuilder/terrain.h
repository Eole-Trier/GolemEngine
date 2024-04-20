#pragma once

#include <vector>

#include "Resource/Rendering/shader.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/vertex.h"

struct t_Vertex
{
    Vector3 position;
    Vector2 textureCoords;
};

class Terrain
{
private:
    Texture* m_texture = nullptr;
    Shader* m_shader = nullptr;
    std::vector<t_Vertex> m_vertices;
    std::vector<int> m_indices;
    
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
    
public:
    int xSize;
    int zSize;

public:
    Terrain(int _xSize, int _zSize);

    void SetupMesh();
    void Draw();
};
