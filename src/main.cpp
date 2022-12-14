#include "ConsoleProcessor.h"

#include <spdlog/spdlog.h>

#include <cxxopts.hpp>

int main(int argc, char *argv[])
{
	spdlog::set_level(spdlog::level::off);
	spdlog::info("Started program");

	console::ConsoleParser consoleParser;

	try
	{
		consoleParser.parse(argc, argv);
	}
	catch (const cxxopts::exceptions::parsing& ex)
	{
		std::cerr << ex.what() << std::endl;
		spdlog::error(ex.what());
		return EXIT_FAILURE;
	}

	console::ConsoleParser::ConsoleParam params = consoleParser.getConsoleParam();

	int processResult =  console::processConsoleParam(params);
	spdlog::info("Program end");
	return processResult;
}
