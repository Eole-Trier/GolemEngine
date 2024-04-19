#pragma once

#include <vector>

#include "dll.h"
#include "terrain.h"


class GOLEM_ENGINE_API WorldBuilder
{
private:
    static inline Terrain* m_terrain = nullptr;

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
    static void RenderTerrainData();
    static void RenderTerrain();

    static Terrain* GetTerrain();
};