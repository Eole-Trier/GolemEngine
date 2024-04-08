#include "Resource/tools.h"

#include <filesystem>
#include <string>
#include <iostream>

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

    int GOLEM_ENGINE_API GetFolderSize(std::filesystem::path _pathToFolder)
    {
        int fileCount = 0;
        try
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(_pathToFolder))
            {
                if (std::filesystem::is_regular_file(entry))
                {
                    fileCount++;
                }
            }
            std::cout << "Number of files: " << fileCount << std::endl;
        }
        catch (const std::exception& _e)
        {
            std::cerr << "Error: " << _e.what() << std::endl;
            return 0;
        }
        return fileCount;
    }
}