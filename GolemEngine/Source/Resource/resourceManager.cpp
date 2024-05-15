#include "Resource/resourceManager.h"
#include "Resource/Rendering/model.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/shader.h"
#include "Utils/tools.h"

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

    m_defaultTexture = "default_texture";
    m_defaultModel = "default_model";
    m_defaultShader = "default_shader";
    // TODO set default model and texture to cube and default texture

    Texture* defaultTexture = resourceManager->Create<Texture>(m_defaultTexture, Tools::FindFile("default_texture.png"));
    defaultTexture->Load(defaultTexture->path.c_str());

    Model* defaultModel = resourceManager->Create<Model>(m_defaultModel, Tools::FindFile("cube.obj"));
    defaultModel->Load(defaultModel->path.c_str());

    Model* sphere = resourceManager->Create<Model>("sphere", Tools::FindFile("sphere.obj"));
    sphere->Load(sphere->path.c_str());

    Model* cube = resourceManager->Create<Model>("cube", Tools::FindFile("cube.obj"));
    cube->Load(cube->path.c_str());

    Shader* defaultShader = resourceManager->Create<Shader>(m_defaultShader, Tools::FindFile("default.vs"));
    defaultShader->SetVertexAndFragmentShader(defaultShader->path.c_str(), Tools::FindFile("default.fs").c_str());

    Shader* sphereColliderShader = resourceManager->Create<Shader>("sphereCollider", Tools::FindFile("sphereCollider.vs"));
    sphereColliderShader->SetVertexAndFragmentShader(sphereColliderShader->path.c_str(), Tools::FindFile("sphereCollider.fs").c_str());

    Shader* boxColliderShader = resourceManager->Create<Shader>("boxCollider", Tools::FindFile("boxCollider.vs"));
    boxColliderShader->SetVertexAndFragmentShader(boxColliderShader->path.c_str(), Tools::FindFile("boxCollider.fs").c_str());
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
