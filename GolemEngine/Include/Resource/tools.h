#pragma once

#include <string>

#include "dll.h"


namespace Tools
{
	std::string GOLEM_ENGINE_API FindFile(const std::string& _file);
	std::string GOLEM_ENGINE_API FindFolder(const std::string& _folderName);
}