#pragma once

#include <vector>

#include "terrain.h"


class WorldBuilder
{
private:
    std::vector<Terrain*> m_terrains;

public:
    // Private constructors and destructor to make static class
    WorldBuilder() = delete;
    WorldBuilder(WorldBuilder& _other) = delete;
    WorldBuilder(WorldBuilder&& _other) = delete;
    WorldBuilder& operator=(WorldBuilder& _other) = delete;
    WorldBuilder& operator=(WorldBuilder&& _other) = delete;
    void operator=(const WorldBuilder&) = delete;
    ~WorldBuilder() = delete;
};