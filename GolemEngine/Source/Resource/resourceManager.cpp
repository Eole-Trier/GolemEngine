#include "Resource/resourceManager.h"
#include "Utils/tools.h"
#include "Resource/Rendering/model.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/Shader/shader.h"
#include "Resource/Rendering/Shader/computeShader.h"
#include "Resource/Rendering/Shader/vertexShader.h"
#include "Resource/Rendering/Shader/fragmentShader.h"
#include "Resource/Rendering/skybox.h"
#include "Utils/viewportTools.h"

ResourceManager* ResourceManager::m_instancePtr = nullptr;

void ResourceManager::ProcessFile(const std::filesystem::path& _filePath)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    std::string fileName = _filePath.filename().string();
    std::string extension = _filePath.extension().string();
    std::string filePath = _filePath.string();

    if (extension == ".obj")
    {
        Model* model = resourceManager->Create<Model>(fileName, filePath);
        model->Load(filePath.c_str());
    }
    else if (extension == ".jpg" || extension == ".png")
    {
        Texture* texture = resourceManager->Create<Texture>(fileName, filePath);
        texture->Load(filePath.c_str());
    }
}

void ResourceManager::TraverseDirectoryAndLoadFiles(const std::filesystem::path& _directoryPath)
{
    for (const auto& entry : std::filesystem::directory_iterator(_directoryPath))
    {
        if (entry.is_regular_file())
        {
            ProcessFile(entry.path());
        }
        else if (entry.is_directory())
        {
            TraverseDirectoryAndLoadFiles(entry.path());
        }
    }
}

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
    Shader* terrainShader = resourceManager->Create<Shader>(m_terrainShader0);
    VertexShader* terrainVertexShader = new VertexShader(terrainShader, Tools::FindFile("terrain.vs").c_str());
    FragmentShader* terrainFragmentShader = new FragmentShader(terrainShader, Tools::FindFile("terrainHeightmap.fs").c_str());
    terrainShader->SetAllShaders(terrainVertexShader, terrainFragmentShader); 
    
    // Set default texture shader for terrains
    Shader* terrainTextureShader = resourceManager->Create<Shader>(m_terrainShader1);
    VertexShader* terrainVertexTextureShader = new VertexShader(terrainTextureShader, Tools::FindFile("terrain.vs").c_str());
    FragmentShader* terrainTextureFragmentShader = new FragmentShader(terrainTextureShader, Tools::FindFile("terrainTexture.fs").c_str());
    terrainTextureShader->SetAllShaders(terrainVertexTextureShader, terrainTextureFragmentShader);

    Shader* boxColliderShader = resourceManager->Create<Shader>(m_boxColliderShader);
    VertexShader* boxColliderVertexShader = new VertexShader(boxColliderShader, Tools::FindFile("boxCollider.vs").c_str());
    FragmentShader* boxColliderFragmentShader = new FragmentShader(boxColliderShader, Tools::FindFile("boxCollider.fs").c_str());
    boxColliderShader->SetAllShaders(boxColliderVertexShader, boxColliderFragmentShader);
    
    Shader* skyboxShader = resourceManager->Create<Shader>(m_skyboxShader);
    VertexShader* skyboxVertexShader = new VertexShader(skyboxShader, Tools::FindFile("skybox.vs").c_str());
    FragmentShader* skyboxFragmentShader = new FragmentShader(skyboxShader, Tools::FindFile("skybox.fs").c_str());

    skyboxShader->SetAllShaders(skyboxVertexShader, skyboxFragmentShader);
    Skybox::GetInstance().SetTexture();
    skyboxShader->Use();
    skyboxShader->GetFragmentShader()->SetInt("skybox", 0);

    // Create the default compute shader for terrains
    ComputeShader* defaultTerrainComputeShader = resourceManager->Create<ComputeShader>(m_terrainComputeShader);
    defaultTerrainComputeShader->SetComputePath(Tools::FindFile("terrain.comp"));
    defaultTerrainComputeShader->Init();
    
    Texture* defaultTexture = resourceManager->Create<Texture>(m_defaultTexture, Tools::FindFile("default_texture.png"));
    defaultTexture->Load(defaultTexture->path.c_str());

    Texture* defaultGridTerrainTexture = resourceManager->Create<Texture>(m_defaultGridTerrainTexture, Tools::FindFile("grid_2.png"));
    defaultGridTerrainTexture->Load(defaultGridTerrainTexture->path.c_str());

    Texture* vikingTexture = resourceManager->Create<Texture>("viking_texture", Tools::FindFile("viking_room.jpg"));
    vikingTexture->Load(vikingTexture->path.c_str());

    Texture* allBaldTexture = resourceManager->Create<Texture>("all_bald_texture", Tools::FindFile("all_bald.jpg"));
    allBaldTexture->Load(allBaldTexture->path.c_str());

    Model* vikingModel = resourceManager->Create<Model>("viking_room", Tools::FindFile("viking_room.obj"));
    vikingModel->Load(vikingModel->path.c_str());

    Model* defaultModel = resourceManager->Create<Model>(m_defaultModel, Tools::FindFile("cube.obj"));
    defaultModel->Load(defaultModel->path.c_str());

    // Needed to avoid same resource reference problem for colliders
    Model* sphere = resourceManager->Create<Model>("sphereCollider.obj", Tools::FindFile("sphere.obj"));
    sphere->Load(sphere->path.c_str());

    Model* cube = resourceManager->Create<Model>("cubeCollider.obj", Tools::FindFile("cube.obj"));
    cube->Load(cube->path.c_str());
}

std::string ResourceManager::GetDefaultShader()
{
    return m_defaultShader;
}

std::string ResourceManager::GetDefaultTexture()
{
    return m_defaultTexture;
}

std::string ResourceManager::GetDefaultModel()
{
    return m_defaultModel;
}

std::string ResourceManager::GetDefaultTerrainShader()
{
    return m_terrainShader0;
}

std::string ResourceManager::GetDefaultTerrainTextureShader()
{
    return m_terrainShader1;
}

std::string ResourceManager::GetDefaultTerrainComputeShader()
{
    return m_terrainComputeShader;
}

std::string ResourceManager::GetDefaultGridTerrainTexture()
{
    return m_defaultGridTerrainTexture;
}