#pragma once

#include <vector>
#include <nlohmann/json.hpp>
#include <string>

#include "dll.h"
#include "Components/transform.h"
#include "Resource/Rendering/shader.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/vertex.h"
#include "Resource/guid.h"
#include "Core/camera.h"
#include "vector2.h"

using json = nlohmann::json;


class Terrain
{
protected:
    std::vector<Vertex> m_vertices;
    std::vector<int> m_indices;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;

    Shader* m_shader = nullptr;
    float m_yMax = 0.0f;    // Store the heighest y value of the noise map to pass it to the shader
    int m_xResolution = 2;    // To set the amount of vertices in x (a terrin with 4 vertices or 255 will have a similar, so it's for vertex details)
    int m_zResolution = 2;    // To set the amount of vertices in z
    Vector2 m_size = {1.0f, 1.0f};    // To set the size of the terrain

    size_t m_id;

public:
    Guid guid;
    std::string name;
    Transform* transform = nullptr;

public:
    GOLEM_ENGINE_API Terrain() = default;

    GOLEM_ENGINE_API void SetupMesh();
    GOLEM_ENGINE_API void Draw(Camera* _camera);
    GOLEM_ENGINE_API size_t GetId();
    
    GOLEM_ENGINE_API virtual void Init(int _xResolution, int _zResolution, Vector2 _size) {}
    GOLEM_ENGINE_API virtual void Init(const char* _noisemapPath, Vector2 _size, float _amplitude) {}

#pragma region Noisemap terrain functions
    GOLEM_ENGINE_API virtual std::string GetNoisemapPath() { return {}; }

    GOLEM_ENGINE_API virtual void SetNoisemapPath(std::string _noisemapPath) {}
#pragma endregion Noisemap terrain functions


    virtual void ToJson(json& _j) const {};    // Virtual function to serialize component to JSON
};
