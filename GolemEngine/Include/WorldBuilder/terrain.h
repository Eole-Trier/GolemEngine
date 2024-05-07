#pragma once

#include <vector>
#include <nlohmann/json.hpp>
#include <string>

#include "dll.h"
#include "Components/transform.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/vertex.h"
#include "Resource/guid.h"
#include "Core/camera.h"
#include "vector2.h"
#include "Core/gameobject.h"
#include "Resource/Rendering/Shader/computeShader.h"
#include "matrix4.h"

using json = nlohmann::json;



class Terrain : public GameObject
{
protected:
    std::vector<Vertex> m_vertices;
    std::vector<int> m_indices;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
    unsigned int m_ssbo;
    Shader* m_shader = nullptr;
    ComputeShader* m_computeShader = nullptr;

    float m_yMin = 0.0f;    // Store the lowest y value of the noise map to pass it to the shader
    float m_yMax = 0.0f;    // Store the heighest y value of the noise map to pass it to the shader
    int m_xResolution = 2;    // To set the amount of vertices in x (a terrin with 4 vertices or 255 will have a similar, so it's for vertex details)
    int m_zResolution = 2;    // To set the amount of vertices in z

    Matrix4 m_oldModelMatrix;

public:
    Terrain(std::string _name, Transform* _transform);
    ~Terrain();

    void SetupMesh();
    void UseComputeShader();
    void Draw(Camera* _camera);
    void GetComputeShaderData(Camera* _camera);
    
    virtual void Init(int _xResolution, int _zResolution) {}
    virtual void Init(const char* _noisemapPath) {}

#pragma region Noisemap terrain functions
    virtual std::string GetNoisemapPath() { return {}; }

    virtual void SetNoisemapPath(std::string _noisemapPath) {}
#pragma endregion Noisemap terrain functions


    virtual void ToJson(json& _j) const {};    // Virtual function to serialize component to JSON
};
