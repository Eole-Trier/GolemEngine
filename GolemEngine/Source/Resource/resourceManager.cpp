#include "Resource/resourceManager.h"

#include "Utils/tools.h"
#include "Resource/Rendering/Shaders/shader.h"
#include "Resource/Rendering/Shaders/vertexShader.h"
#include "Resource/Rendering/Shaders/fragmentShader.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/model.h"
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

    VertexShader* defaultVertexShader = resourceManager->Create<VertexShader>(m_defaultVertexShader, Tools::FindFile("default.vs"));
    FragmentShader* defaultFragmentShader = resourceManager->Create<FragmentShader>(m_defaultFragmentShader, Tools::FindFile("default.fs"));
    Shader* defaultShader = new Shader(defaultVertexShader, defaultFragmentShader);
    
    // Shader* defaultShader = resourceManager->Create<Shader>(m_defaultShader, Tools::FindFile("default.vs"));
    // defaultShader->SetVertexFragmentComputeShaders(defaultShader->path.c_str(), Tools::FindFile("default.fs").c_str(), Tools::FindFile("default.comp").c_str());

    // Shader* defaultTerrainShader = resourceManager->Create<Shader>(m_defaultTerrainShader, Tools::FindFile("defaultTerrain.vs"));
    // defaultTerrainShader->SetVertexFragmentComputeShaders(defaultTerrainShader->path.c_str(), Tools::FindFile("defaultTerrain.fs").c_str(), Tools::FindFile("default.comp").c_str());

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

std::string ResourceManager::GetDefaultTexture()
{
    return m_defaultTexture;
}

std::string ResourceManager::GetDefaultModel()
{
    return m_defaultModel;
}
