#pragma once

#include <nlohmann/json.hpp>

#include "terrain.h"

using json = nlohmann::json;


class DefaultTerrain : public Terrain
{
public:
    GOLEM_ENGINE_API DefaultTerrain(std::string _name, Transform* _transform);
    
    GOLEM_ENGINE_API void Init(int _xResolution, int _zResolution) override;

    
    // Define serialization and deserialization functions manually because the
    // macro is not used due to the pointer member variable.
    void ToJson(json& _j) const override
    {
        _j = json
        {
            {"xResolution", xResolution},
            {"zResolution", zResolution},
            {"noisemapPath", ""},
        };
    }
};