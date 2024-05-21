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


struct VertexGpu
{
    Vertex vertex;
    float padding1;
    float padding2;
    Vector2 padding3;
};

class Terrain : public GameObject
{
protected:
    std::vector<VertexGpu> m_vertices;
    std::vector<int> m_indices;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
    unsigned int m_ssboIn;
    unsigned int m_ssboOut;
    std::vector<Shader*> m_shaders;
    ComputeShader* m_computeShader = nullptr;
    Texture* m_texture = nullptr;

    float m_yMin = 0.0f;    // Store the lowest y value of the noise map to pass it to the shader
    float m_yMax = 0.0f;    // Store the heighest y value of the noise map to pass it to the shader

    Matrix4 m_oldModelMatrix;    // To check if there were any modifcations made to the terrain

public:
    int xResolution = 2;    // To set the amount of vertices in x (a terrin with 4 vertices or 255 will have a similar, so it's for vertex details)
    int zResolution = 2;    // To set the amount of vertices in z

public:
    GOLEM_ENGINE_API Terrain(std::string _name, Transform* _transform);
    GOLEM_ENGINE_API ~Terrain();

    GOLEM_ENGINE_API void SetupMesh();
    GOLEM_ENGINE_API void UseComputeShader();
    GOLEM_ENGINE_API void Draw(Camera* _camera);
    GOLEM_ENGINE_API void UpdateLights(Shader* _shader);
    GOLEM_ENGINE_API void GetComputeShaderData(Camera* _camera);
    GOLEM_ENGINE_API std::vector<VertexGpu> GetVerticesGpu();
    GOLEM_ENGINE_API std::vector<Vertex> GetVertices();
    GOLEM_ENGINE_API void CalculateNormals();
    
    GOLEM_ENGINE_API virtual void Init(int _xResolution, int _zResolution) {}
    GOLEM_ENGINE_API virtual void Init(const char* _noisemapPath) {}

#pragma region Noisemap terrain functions
    GOLEM_ENGINE_API virtual std::string GetNoisemapPath() { return {}; }

    GOLEM_ENGINE_API virtual void SetNoisemapPath(std::string _noisemapPath) {}
#pragma endregion Noisemap terrain functions


    GOLEM_ENGINE_API virtual void ToJson(json& _j) const {};    // Virtual function to serialize component to JSON
};
