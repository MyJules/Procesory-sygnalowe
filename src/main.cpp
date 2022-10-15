#include "ConsoleProcessor.h"

#include <iostream>

#include <cxxopts.hpp>

int main(int argc, char *argv[])
{
	parser::ConsoleParser consoleParser;

	try
	{
		consoleParser.parse(argc, argv);
	}
	catch (const cxxopts::exceptions::parsing& ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	parser::ConsoleParser::ConsoleParam params = consoleParser.getConsoleParam();

	processor::processConsoleParams(params);

	return EXIT_SUCCESS;
}
