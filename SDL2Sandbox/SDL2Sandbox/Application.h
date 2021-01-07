#pragma once
#include "SDL.h"
#include <string>
#include <vector>
class Application
{
public:
	static int Run(const std::vector<std::string>& arguments);
};

