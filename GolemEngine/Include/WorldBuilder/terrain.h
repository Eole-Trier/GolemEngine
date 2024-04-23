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
    std::vector<Vertex> p_vertices;
    std::vector<int> p_indices;
    unsigned int p_vao;
    unsigned int p_vbo;
    unsigned int p_ebo;

    Shader* p_shader = nullptr;
    float p_yMax = 0.0f;    // Store the heighest y value of the noise map to pass it to the shader
    int p_xResolution = 2;    // To set the amount of vertices in x (a terrin with 4 vertices or 255 will have a similar, so it's for vertex details)
    int p_zResolution = 2;    // To set the amount of vertices in z
    Vector2 p_size = {1.0f, 1.0f};    // To set the size of the terrain

public:
    Guid guid;
    std::string name;    

public:
    GOLEM_ENGINE_API Terrain() = default;

    GOLEM_ENGINE_API void SetupMesh();
    GOLEM_ENGINE_API void Draw(Camera* _camera);

    GOLEM_ENGINE_API virtual void Init(int _xResolution, int _zResolution, Vector2 _size) {}
    GOLEM_ENGINE_API virtual void Init(const char* _noisemapPath, Vector2 _size, float _amplitude) {}

#pragma region Noisemap terrain functions
    GOLEM_ENGINE_API virtual std::string GetNoisemapPath() { return {}; }

    GOLEM_ENGINE_API virtual void SetNoisemapPath(std::string _noisemapPath) {}
#pragma endregion Noisemap terrain functions


    virtual void ToJson(json& _j) const {};    // Virtual function to serialize component to JSON
};
