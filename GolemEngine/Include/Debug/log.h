#pragma once

#include <filesystem>
#include <fstream>
#include "dll.h"

class GOLEM_ENGINE_API Log
{
public:
	Log() {};
	~Log();

	static void OpenFile(std::filesystem::path const& filename);
	static void Print(const char* format, ...);

private:
	static std::fstream mFile;
};