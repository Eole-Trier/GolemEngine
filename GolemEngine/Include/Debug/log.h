#pragma once

#include <filesystem>
#include <fstream>

class Log
{
public:
	Log() {};
	~Log();

	static void OpenFile(std::filesystem::path const& filename);
	static void Print(const char* format, ...);

private:
	static std::fstream mFile;
};