#pragma once

#include <vector>
#include <nlohmann/json.hpp>
#include <string>

#include "dll.h"
#include "Components/transform.h"
#include "Resource/Rendering/Shaders/shader.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/vertex.h"
#include "Resource/guid.h"
#include "Core/camera.h"
#include "vector2.h"
#include "Core/gameobject.h"

using json = nlohmann::json;


class Terrain : public GameObject
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

    size_t m_id;

public:
    Terrain(std::string _name, Transform* _transform);
    ~Terrain();

    void SetupMesh();
    void Draw(Camera* _camera);
    size_t GetId();
    
    virtual void Init(int _xResolution, int _zResolution) {}
    virtual void Init(const char* _noisemapPath) {}

#pragma region Noisemap terrain functions
    virtual std::string GetNoisemapPath() { return {}; }

    virtual void SetNoisemapPath(std::string _noisemapPath) {}
#pragma endregion Noisemap terrain functions


    virtual void ToJson(json& _j) const {};    // Virtual function to serialize component to JSON
};
