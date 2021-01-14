#include "Application.h"
#include <stdlib.h>
#include <time.h>
int main(int argc, char** argv)
{
	srand((unsigned int)time(nullptr));
	std::vector<std::string> arguments(argc);
	for (int index = 0; index < argc; ++index)
	{
		arguments.push_back(std::string(argv[index]));
	}
	return tggd::common::Application::Run(arguments);
}