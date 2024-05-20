#pragma once

#include "terrain.h"

#include <nlohmann/json.hpp>

#include "dll.h"

using json = nlohmann::json;


class GOLEM_ENGINE_API NoisemapTerrain : public Terrain
{
private:
    std::string m_noisemapPath;
    int m_nChannel;
    
public:
    NoisemapTerrain(std::string _name, Transform* _transform);
    
    void Init(const char* _noisemapPath) override;

    std::string GetNoisemapPath() override;

    void SetNoisemapPath(std::string _noisemapPath) override;
    
    
    // Define serialization and deserialization functions manually because the
    // macro is not used due to the pointer member variable.
    void ToJson(json& _j) const override
    {
        _j = json
        {
            {"xResolution", xResolution},
            {"zResolution", zResolution},
            {"noisemapPath", m_noisemapPath}
        };
    }
};