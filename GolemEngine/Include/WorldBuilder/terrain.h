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
    
    int m_nChannel;    // For the noisemap
    float m_yMax = 0.0f;    // Store the heighest y value of the noise map to pass it to the shader
    
    int m_xResolution;    // To set the amount of vertices in x (a terrin with 4 vertices or 255 will have the same size, so it's for vertex details)
    int m_zResolution;    // To set the amount of vertices in z
    Vector2 m_size;    // To set the size of the terrain

public:
    Terrain(int _xResolution, int _zResolution, Vector2 _size);
    Terrain(const char* _noisemapPath, Vector2 _size, float _amplitude);

    void SetupMesh();
    void Draw(Camera* _camera);
};
