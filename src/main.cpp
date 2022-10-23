#include "ConsoleProcessor.h"

#include <iostream>

#include <cxxopts.hpp>

int main(int argc, char *argv[])
{
	console::ConsoleParser consoleParser;

	try
	{
		consoleParser.parse(argc, argv);
	}
	catch (const cxxopts::exceptions::parsing& ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	console::ConsoleParser::ConsoleParam params = consoleParser.getConsoleParam();

	return console::processConsoleParam(params);
}
