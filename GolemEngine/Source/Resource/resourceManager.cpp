#include "Resource/resourceManager.h"
#include "Resource/Rendering/model.h"
#include "Resource/Rendering/texture.h"

ResourceManager* ResourceManager::m_instancePtr = nullptr;

void ResourceManager::ProcessFile(const std::filesystem::path& _filePath)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    std::string fileName = _filePath.filename().string();
    std::string extension = _filePath.extension().string();
    std::string filePath = _filePath.string();
    std::cout << fileName << std::endl;

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