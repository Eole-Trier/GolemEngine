#pragma once

#include <nlohmann/json.hpp>

#include "terrain.h"

using json = nlohmann::json;


class DefaultTerrain : public Terrain
{
public:
    GOLEM_ENGINE_API DefaultTerrain();
    
    GOLEM_ENGINE_API void Init(int _xResolution, int _zResolution, Vector2 _size) override;

    
    // Define serialization and deserialization functions manually because the
    // macro is not used due to the pointer member variable.
    void ToJson(json& _j) const override
    {
        _j = json
        {
            {"name", name},
            {"guid", guid.ToString()},
            {"xResolution", m_xResolution},
            {"zResolution", m_zResolution},
            {"size", m_size},
            {"noisemapPath", ""},
            {"amplitude", 0}
        };
    }
};