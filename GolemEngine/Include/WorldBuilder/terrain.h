#pragma once


class Terrain
{
public:
    int xSize;
    int zSize;

public:
    Terrain(int _xSize, int _zSize);

    void GenerateTerrainData();
};
