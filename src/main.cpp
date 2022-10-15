#include "EffectCreator.h"
#include "ConsoleParser.h"

#include <string>
#include <iostream>
#include <vector>

#include <cxxopts.hpp>

int processConsoleParams(const ConsoleParser::ConsoleParam& params);

int main(int argc, char *argv[])
{
	ConsoleParser consoleParser;

	try
	{
		consoleParser.parse(argc, argv);
	}
	catch (const cxxopts::exceptions::parsing& ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	ConsoleParser::ConsoleParam params = consoleParser.getConsoleParam();

	processConsoleParams(params);

	return EXIT_SUCCESS;
}


int processConsoleParams(const ConsoleParser::ConsoleParam& params)
{
	if (params.help)
	{
		std::cout << params.helpInfo << std::endl;
		return EXIT_SUCCESS;
	}

	if (params.inputFile.empty())
	{
		std::cerr << "No input file provided, please enter file path" << std::endl;
		return EXIT_FAILURE;
	}
}