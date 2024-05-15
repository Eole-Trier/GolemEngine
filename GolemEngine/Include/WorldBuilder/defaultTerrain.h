#pragma once

#include "terrain.h"

#include <nlohmann/json.hpp>

#include "dll.h"

using json = nlohmann::json;


class GOLEM_ENGINE_API DefaultTerrain : public Terrain
{
public:
    DefaultTerrain(std::string _name, Transform* _transform);
    
    void Init(int _xResolution, int _zResolution) override;

    
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