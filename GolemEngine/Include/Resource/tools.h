#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "dll.h"


namespace Tools
{
	std::string GOLEM_ENGINE_API FindFile(const std::string& _file);
	std::string GOLEM_ENGINE_API FindFolder(const std::string& _folderName);
	std::string GOLEM_ENGINE_API RemoveExtension(const std::string& _fileName);

	int GOLEM_ENGINE_API GetFolderSize(std::filesystem::path _pathToFolder);
	std::vector<std::string> GOLEM_ENGINE_API GetFolderElementsNames(const std::filesystem::path _pathToFolder);
}