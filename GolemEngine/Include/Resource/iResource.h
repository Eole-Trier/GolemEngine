#pragma once
#include <filesystem>


class IResource
{
public:
	virtual void LoadIResource(std::filesystem::path _filepath) = 0;

	void LoadFromPath()
	{
		if (path != "")LoadIResource(path);
	};

	unsigned int ID = 0;
	std::filesystem::path path;
};