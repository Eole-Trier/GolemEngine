#pragma once

#include <string>

#include "dll.h"

#define print(x) std::cout << x << std::endl

namespace Tools
{
	std::string GOLEM_ENGINE_API FindFile(const std::string& _file);
	std::string GOLEM_ENGINE_API FindFolder(const std::string& _folderName);
	// Get the file extentension like .obj .cpp .h ......
	std::string GOLEM_ENGINE_API GetFileExtension(const std::string& _fileName);
}