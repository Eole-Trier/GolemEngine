#include "Resource/resourceManager.h"

#include "Utils/tools.h"
#include "Resource/Rendering/Shader/shader.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/model.h"
#include "Resource/Rendering/Shader/computeShader.h"
#include "Resource/Rendering/Shader/vertexShader.h"
#include "Resource/Rendering/Shader/fragmentShader.h"
#include "Utils/viewportTools.h"


ResourceManager* ResourceManager::m_instancePtr = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
    if (!m_instancePtr) 
    {
        m_instancePtr = new ResourceManager();
    }
    return m_instancePtr;
}

void ResourceManager::CreateAndLoadResources()
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    // Set default shader for general stuff
    Shader* defaultShader = resourceManager->Create<Shader>(m_defaultShader);
    VertexShader* defaultVertexShader = new VertexShader(defaultShader, Tools::FindFile("default.vs").c_str());
    FragmentShader* defaultFragmentShader = new FragmentShader(defaultShader, Tools::FindFile("default.fs").c_str());
    defaultShader->SetAllShaders(defaultVertexShader, defaultFragmentShader);

    // Set default shader for terrains
    Shader* defaultTerrainShader = resourceManager->Create<Shader>(m_defaultTerrainShader);
    VertexShader* defaultTerrainVertexShader = new VertexShader(defaultTerrainShader, Tools::FindFile("defaultTerrain.vs").c_str());
    FragmentShader* defaultTerrainFragmentShader = new FragmentShader(defaultTerrainShader, Tools::FindFile("defaultTerrain.fs").c_str());
    defaultTerrainShader->SetAllShaders(defaultTerrainVertexShader, defaultTerrainFragmentShader);

    // Create the default compute shader for terrains
    ComputeShader* defaultTerrainComputeShader = resourceManager->Create<ComputeShader>(m_defaultTerrainComputeShader);
    defaultTerrainComputeShader->SetComputePath(Tools::FindFile("default.comp"));
    defaultTerrainComputeShader->Init();
    
    Texture* defaultTexture = resourceManager->Create<Texture>(m_defaultTexture, Tools::FindFile("default_texture.png"));
    defaultTexture->Load(defaultTexture->path.c_str());

    Texture* vikingTexture = resourceManager->Create<Texture>("viking_texture", Tools::FindFile("viking_room.jpg"));
    vikingTexture->Load(vikingTexture->path.c_str());

    Texture* allBaldTexture = resourceManager->Create<Texture>("all_bald_texture", Tools::FindFile("all_bald.jpg"));
    allBaldTexture->Load(allBaldTexture->path.c_str());

    Model* vikingModel = resourceManager->Create<Model>("viking_room", Tools::FindFile("viking_room.obj"));
    vikingModel->Load(vikingModel->path.c_str());

    Model* defaultModel = resourceManager->Create<Model>(m_defaultModel, Tools::FindFile("cube.obj"));
    defaultModel->Load(defaultModel->path.c_str());

    Model* sphereModel = resourceManager->Create<Model>("sphere", Tools::FindFile("sphere.obj"));
    sphereModel->Load(sphereModel->path.c_str());

    Model* cubeModel = resourceManager->Create<Model>("cube", Tools::FindFile("cube.obj"));
    cubeModel->Load(cubeModel->path.c_str());
}

std::string ResourceManager::GetDefaultShader()
{
    return m_defaultShader;
}

std::string ResourceManager::GetDefaultTerrainShader()
{
    return m_defaultTerrainShader;
}

std::string ResourceManager::GetDefaultTerrainComputeShader()
{
    return m_defaultTerrainComputeShader;
}

std::string ResourceManager::GetDefaultTexture()
{
    return m_defaultTexture;
}

std::string ResourceManager::GetDefaultModel()
{
    return m_defaultModel;
}
