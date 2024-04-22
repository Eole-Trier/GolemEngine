#pragma once

#include "dll.h"
#include "vector2.h"


class GOLEM_ENGINE_API WorldBuilder
{
private:
    // Private constructors and destructor to make static class
    WorldBuilder() = delete;
    WorldBuilder(WorldBuilder& _other) = delete;
    WorldBuilder(WorldBuilder&& _other) = delete;
    WorldBuilder& operator=(WorldBuilder& _other) = delete;
    WorldBuilder& operator=(WorldBuilder&& _other) = delete;
    void operator=(const WorldBuilder&) = delete;
    ~WorldBuilder() = delete;

public:
    static void Init();
    static void CreateTerrain(int _xResolution, int _zResolution, Vector2 _size);
    static void CreateTerrainNoisemap(const char* _noisemapPath, Vector2 _size, float _amplitude);
};