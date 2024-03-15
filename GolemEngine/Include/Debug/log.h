#pragma once

#include <filesystem>
#include <fstream>

#include "dll.h"


class GOLEM_ENGINE_API Log
{
private:
	static std::fstream m_file;

public:
	Log() {};
	~Log();

	static void OpenFile(std::filesystem::path const& _filename);
	static void Print(const char* _format, ...);
};