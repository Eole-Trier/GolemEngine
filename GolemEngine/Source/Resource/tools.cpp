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
        for (std::filesystem::path file : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
            if (file.filename().string().find(_file) != std::string::npos)
            {
                targetFileName = file.string();
                return targetFileName.c_str();
            }

    }

    
}
