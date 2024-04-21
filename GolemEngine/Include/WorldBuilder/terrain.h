#pragma once

#include <vector>

#include "Components/transform.h"
#include "Resource/Rendering/shader.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/vertex.h"
#include "Core/camera.h"


class Terrain
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<int> m_indices;
    
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;

    Shader* m_shader = nullptr;

    int m_xSize, m_zSize, m_nChannel;
    
public:
    int xResolution;
    int zResolution;
    float generationScale;

public:
    Terrain(int _xResolution, int _zResolution, float _generationScale);
    Terrain(const char* _noisemapPath);

    void SetupMesh();
    void Draw(Camera* _camera);
};
