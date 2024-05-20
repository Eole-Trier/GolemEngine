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

    resourceManager->TraverseDirectoryAndLoadFiles(Tools::FindFolder("Assets"));

    // Set default shader for general stuff
    Shader* defaultShader = resourceManager->Create<Shader>(m_defaultShader);
    VertexShader* defaultVertexShader = new VertexShader(defaultShader, Tools::FindFile("default.vs").c_str());
    FragmentShader* defaultFragmentShader = new FragmentShader(defaultShader, Tools::FindFile("default.fs").c_str());
    defaultShader->SetAllShaders(defaultVertexShader, defaultFragmentShader);

#pragma region Terrain Shaders
    Shader* terrainShader = resourceManager->Create<Shader>(m_terrainShader);
    VertexShader* terrainVertexShader = new VertexShader(terrainShader, Tools::FindFile("terrain.vs").c_str());
    FragmentShader* terrainFragmentShader = new FragmentShader(terrainShader, Tools::FindFile("terrain.fs").c_str());
    terrainShader->SetAllShaders(terrainVertexShader, terrainFragmentShader); 
    
    ComputeShader* defaultTerrainComputeShader = resourceManager->Create<ComputeShader>(m_terrainComputeShader);
    defaultTerrainComputeShader->SetComputePath(Tools::FindFile("terrain.comp"));
    defaultTerrainComputeShader->Init();
#pragma endregion Terrain Shaders

    Shader* sphereColliderShader = resourceManager->Create<Shader>(m_sphereColliderShader);
    VertexShader* sphereColliderVertexShader = new VertexShader(sphereColliderShader, Tools::FindFile("sphereCollider.vs").c_str());
    FragmentShader* sphereColliderFragmentShader = new FragmentShader(sphereColliderShader, Tools::FindFile("sphereCollider.fs").c_str());
    sphereColliderShader->SetAllShaders(sphereColliderVertexShader, sphereColliderFragmentShader);

    Shader* boxColliderShader = resourceManager->Create<Shader>(m_boxColliderShader);
    VertexShader* boxColliderVertexShader = new VertexShader(boxColliderShader, Tools::FindFile("boxCollider.vs").c_str());
    FragmentShader* boxColliderFragmentShader = new FragmentShader(boxColliderShader, Tools::FindFile("boxCollider.fs").c_str());
    boxColliderShader->SetAllShaders(boxColliderVertexShader, boxColliderFragmentShader);

    Shader* meshColliderShader = resourceManager->Create<Shader>(m_meshColliderShader);
    VertexShader* meshColliderVertexShader = new VertexShader(meshColliderShader, Tools::FindFile("meshCollider.vs").c_str());
    FragmentShader* meshColliderFragmentShader = new FragmentShader(meshColliderShader, Tools::FindFile("meshCollider.fs").c_str());
    meshColliderShader->SetAllShaders(meshColliderVertexShader, meshColliderFragmentShader);

    Shader* skyboxShader = resourceManager->Create<Shader>(m_skyboxShader);
    VertexShader* skyboxVertexShader = new VertexShader(skyboxShader, Tools::FindFile("skybox.vs").c_str());
    FragmentShader* skyboxFragmentShader = new FragmentShader(skyboxShader, Tools::FindFile("skybox.fs").c_str());

    skyboxShader->SetAllShaders(skyboxVertexShader, skyboxFragmentShader);
    Skybox::GetInstance().SetTexture();
    skyboxShader->Use();
    skyboxShader->GetFragmentShader()->SetInt("skybox", 0);

    
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

    // Skybox Init
    //Shader* skyboxShader = resourceManager->Create<Shader>("skybox_shader", Tools::FindFile("skybox.vs"));
    //skyboxShader->SetVertexAndFragmentShader(skyboxShader->path.c_str(), Tools::FindFile("skybox.fs").c_str());
    //Skybox::GetInstance().SetTexture();
    //skyboxShader->Use();
    //skyboxShader->SetInt("skybox", 0);
}

void ResourceManager::DeleteAllResouces()
{
    for (auto& resource : m_resources)
    {
        delete resource.second;
    }
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

std::string ResourceManager::GetTerrainShader()
{
    return m_terrainShader;
}

std::string ResourceManager::GetTerrainComputeShader()
{
    return m_terrainComputeShader;
}

std::string ResourceManager::GetGridTerrainTexture()
{
    return m_defaultGridTerrainTexture;
}
std::string ResourceManager::GetSkyboxShader()
{
    return m_skyboxShader;
}

std::string ResourceManager::GetBoxColliderShader()
{
    return m_boxColliderShader;
}

std::string ResourceManager::GetSphereColliderShader()
{
    return m_sphereColliderShader;
}

std::string ResourceManager::GetMeshColliderShader()
{
    return m_meshColliderShader;
}