#pragma once

#include <vector>
#include <vector2.h>
#include <vector3.h>

#include "dll.h"
#include "Resource/Rendering/shader.h"
#include "Resource/Rendering/texture.h"


struct Pixel
{
    Vector2 position;
    int r;    // We just need to store any pixel RGB value since the heightmaps are black and white so R = G = B
};

struct TerrainVertex
{
    Vector3 position;
    Vector2 texturePosition;
};

class GOLEM_ENGINE_API Terrain
{
private:
    int m_width;
    int m_height;
    int m_nChannel;
    unsigned char* m_heightmap;
    std::vector<Pixel> m_pixels;

public:
    std::vector<TerrainVertex> vertices;
    std::vector<int> indices;
    int rows;
    int columns;
    float lowestPoint = 0.0f;
    float highestPoint = 0.0f;

    Shader* shader;
    Texture* texture;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

public:
    Terrain(const char* _imagePath);

    void GenerateVertexData(float _heightmapSizeMultiplier, float _verticesSeparationDist = 0.1f);
    void GenerateIndexData();
};
