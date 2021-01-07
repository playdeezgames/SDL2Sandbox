#include "Application.h"
int main(int argc, char** argv)
{
	std::vector<std::string> arguments(argc);
	for (int index = 0; index < argc; ++index)
	{
		arguments.push_back(std::string(argv[index]));
	}
	return Application::Run(arguments);
}