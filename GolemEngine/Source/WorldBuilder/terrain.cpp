#include "WorldBuilder/terrain.h"

#include <Image/stb_image.h>
#include <iostream>


Terrain::Terrain(const char* _imagePath)
{
    m_heightmap = stbi_load(_imagePath, &m_width, &m_height, &m_nChannel, STBI_grey);
}

void Terrain::GenerateVertexData(float _heightmapSizeMultiplier, float _verticesSeparationDist)
{
    int bytePerPixel = 1;

    // Load the heightmap and store is dimensions
    std::cout << "heightmap dimensions: " << m_width << "x " << m_height << "z" << std::endl;
    rows = m_width * _heightmapSizeMultiplier;
    columns = m_height * _heightmapSizeMultiplier;

    // Initialize a grid of vertices using the heightmap's dimensions
    float z = -50;    // Offset for z to see in scene
    // Make the grid
    for (int i = 0; i < rows; i++)
    {
        float x = -30;    // initialize the start position of a vertex' x
        for (int j = 0; j < columns; j++)
        {
            unsigned char heightmapValue = (m_heightmap + (i + m_width * j) * bytePerPixel)[0];    // Find the pixel value of the heightmap
            TerrainVertex vertex;
            vertex.position.x = x + i * 60.0f / m_width;
            vertex.position.z = z + j * 60.0f / m_height;
            vertex.position.y = heightmapValue / 255.0f * 5;
            
            if (vertex.position.y > highestPoint)
            {
                highestPoint = vertex.position.y;    // Store the highest point of the height,ap
            }

            vertex.texturePosition.x = (1.0f / columns * j);
            vertex.texturePosition.y = (1 - i * 1.0f / rows);
            vertices.push_back(vertex);
        }
    }
}

void Terrain::GenerateIndexData()
{
    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < columns; j++)
        {
            indices.push_back((i - 1) * columns + j - 1);
            indices.push_back((i - 1) * columns + j);
            indices.push_back(i * columns + j - 1);

            indices.push_back(i * columns + j - 1);
            indices.push_back((i - 1) * columns + j);
            indices.push_back(i * columns + j);
        }
    }
}
