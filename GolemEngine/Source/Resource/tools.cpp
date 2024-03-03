
#include "Resource/tools.h"
#include "dll.h"
#include <filesystem>
#include <string>
#include <iostream>

std::string GOLEM_ENGINE_API FindFile(const std::string& pFile) {
    std::string targetFileName;
    for (std::filesystem::path file : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
        if (file.filename().string().find(pFile) != std::string::npos)
        {
            targetFileName = file.string();
            std::cout << targetFileName.c_str() << std::endl;
            return targetFileName.c_str();
        }
}
