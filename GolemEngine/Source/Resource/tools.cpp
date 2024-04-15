#include "Resource/tools.h"

#include <filesystem>
#include <string>
#include <iostream>
#include <stack>

#include "dll.h"

namespace Tools
{
    std::string GOLEM_ENGINE_API FindFile(const std::string& _file) 
    {
        std::string targetFileName;
        for (const auto& file : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
        {
            if (file.path().filename().string().find(_file) != std::string::npos)
            {
                return file.path().string();
            }
        }
        std::cout << "Didn't find the file: " << _file << std::endl;
        return ""; // Return an empty string
    }
    
    std::string GOLEM_ENGINE_API FindFolder(const std::string& _folderName)
    {
        for (const auto& dir : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
        {
            if (dir.is_directory() && dir.path().filename().string().find(_folderName) != std::string::npos)
            {
                return dir.path().string();
            }
        }

        // If the folder is not found, output a message
        std::cout << "Not found the folder: " << _folderName << std::endl;
        return ""; // Return an empty string
    }

    std::string GOLEM_ENGINE_API GetFileExtension(const std::string& _fileName)
    {
        size_t dotPosition = _fileName.find_last_of('.');
        if (dotPosition != std::string::npos)
        {
            return _fileName.substr(dotPosition);
        }
        return "";
    }

    int GOLEM_ENGINE_API GetFolderSize(std::filesystem::path _pathToFolder)
    {
        int fileCount = 0;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(_pathToFolder))
        {
            if (std::filesystem::is_regular_file(entry))
            {
                fileCount++;
            }
        }
        return fileCount;
    }

    std::vector<std::string> GetFolderElementsNames(const std::filesystem::path _pathToFolder)
    {
        std::vector<std::string> elements;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(_pathToFolder))
        {
            if (std::filesystem::is_regular_file(entry))
            {
                elements.push_back(entry.path().filename().string());
            }
            else if (std::filesystem::is_directory(entry))
            {
                elements.push_back(entry.path().filename().string() + " [directory]");
            }
        }
        return elements;
    }

    std::string GOLEM_ENGINE_API RemoveExtension(const std::string& _filename) {
        size_t lastDot = _filename.find_last_of(".");
        if (lastDot != std::string::npos) {
            return _filename.substr(0, lastDot);
        }
        return _filename;
    }
}