#pragma once

#include "dll.h"

#include <string>


class GOLEM_ENGINE_API Resource
{
public:
	Resource() {};
	virtual ~Resource() {};

	std::string path;
};