#pragma once

#include <nlohmann/json.hpp>

#include "terrain.h"

using json = nlohmann::json;


class NoisemapTerrain : public Terrain
{
private:
    std::string m_noisemapPath;
    float m_amplitude;
    int m_nChannel;
    
public:
    GOLEM_ENGINE_API NoisemapTerrain();
    
    GOLEM_ENGINE_API void Init(const char* _noisemapPath, Vector2 _size, float _amplitude) override;

    GOLEM_ENGINE_API std::string GetNoisemapPath() override;

    GOLEM_ENGINE_API void SetNoisemapPath(std::string _noisemapPath) override;
    
    
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
            {"noisemapPath", m_noisemapPath},
            {"amplitude", m_amplitude}
        };
    }
};