#pragma once

#include <filesystem>
#include <string>

#include "dll.h"


namespace Tools
{
	std::string GOLEM_ENGINE_API FindFile(const std::string& _file);
	std::string GOLEM_ENGINE_API FindFolder(const std::string& _folderName);

	int GOLEM_ENGINE_API GetFolderSize(std::filesystem::path _pathToFolder);
}